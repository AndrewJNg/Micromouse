///////////////////////////////////////////////////////////////////////
#include "MT6701.h"
#include <cmath>

// Encoder parameters
#define wheelRadius 17.0
#define MAX_ACCELERATION 1000  // mm/s/s
#define MAX_VELOCITY 1000      // mm/s

#define encoder_tick_per_rev 4096

// Motor parameter
#define PWMResolution 12
#define PWMResolutionMaxValue 4095


// Left encoder I2C pins
#define SDA_1 21
#define SCL_1 22

// Right encoder I2C pins
#define SDA_2 18
#define SCL_2 19

// System speed
#define i2c_speed 400000
#define motor_update_freq 200.0  // 200Hz -> update time -> 5ms

typedef struct MotionParameters {
  float ta;
  float tc;
  float tcf;
  float T;
  float Vm;
  float s_req;
  float velocity;
  float acceleration;
  float time_step;
  int32_t prev_time;

} MotionParameters;

class MotorControl {
private:
  // Classes used
  MT6701 encoder;

  // Variables for multi-turn position tracking
  double previousAngle = 0;
  double cumulativeAngle = 0;
  bool encoderInitialized = false;
  int encoder_dir = 1;

  // Motor properties
  byte motorPin1;
  byte motorPin2;
  byte motorPWM;
  int drive_dir = 1;  // 1 for normal, -1 for inverted direction setup

  // System setup
  int motor_update_interval = 0;  // matches motor_update_freq in time interval (updated in setup)

  double integral_error = 0;
  double prev_error = 0;
  double previous_measurement = 0;

  unsigned long prevMillis = 0;
  double prev_distance = 0;
  double prev_velocity_Millis = 0;


  double prev_velocity = 0;
  double m_previous_fwd_error = 0;
  double prev_FF_velocity =0;


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
  ///////////////////////////
  double m_fwd_error = 0;
  double Tm = 0;

  // Feedforward constants
  double FF_K_offset = 100;
  double FF_K_velocity = 8;
  double FF_K_accel = 0;

  ///////////////////////////
  // PID constants
  double PID_BIAS = 0;
  double PID_Kp = 0;
  double PID_Ki = 0;
  double PID_Kd = 0;

  double err = 0;
  double measured_velocity = 0;

  ////////////////////////////////////////////// Setup ////////////////////////////////////////////////////////////////////
  MotorControl(byte pin1, byte pin2, byte pwm, TwoWire &wire)
    : motorPin1(pin1),
      motorPin2(pin2),
      motorPWM(pwm) {
    encoder.initializeI2C(&wire);
  }

  // void setupEncoder(bool clockwise) {
  //   encoder.begin();
  // encoder.setDirection(clockwise ? AS5600_COUNTERCLOCK_WISE : AS5600_CLOCK_WISE);
  // }
  void setupEncoder(bool clockwise) {
    encoder_dir = clockwise ? 1 : -1;
    double angle = encoder.angleRead();
    previousAngle = angle;
    cumulativeAngle = 0;

    encoderInitialized = true;
  }

  void setupMotor(int direction = 1) {
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    ledcAttach(motorPWM, 5000, PWMResolution);

    stopMotor();
    drive_dir = (direction == 1 || direction == -1) ? direction : 1;  // Ensure drive_dir is either 1 or -1
    motor_update_interval = 1000.0 / motor_update_freq;               //in ms
    PID_Kd = PID_Kd * motor_update_freq;
  }
  //////////////////////////////////////////////// Encoder feedback //////////////////////////////////////////////////////////////////
  // Encoder distance
  // double updateEncoder() {
  //   /////////////////// Library cummulative calculation ///////////////
  //   double currAngle = encoder.getCumulativePosition(1);
  //   return currAngle;
  // }
  double updateEncoder() {
    double currentAngle = encoder.angleRead();

    if (!encoderInitialized) {
      previousAngle = currentAngle;
      encoderInitialized = true;
      return cumulativeAngle;
    }

    // Calculate change in angle
    double deltaAngle = currentAngle - previousAngle;

    // Handle wrap-around
    if (deltaAngle > 180.0) {
      deltaAngle -= 360.0;
    } else if (deltaAngle < -180.0) {
      deltaAngle += 360.0;
    }

    // Apply encoder direction
    cumulativeAngle += deltaAngle * encoder_dir;

    previousAngle = currentAngle;

    return cumulativeAngle;
  }

  double angle2mm() {
    return (2.0 * M_PI * wheelRadius * updateEncoder()) / 360.0;
  }

  //////////////////////////////////////////////// Motor control //////////////////////////////////////////////////////////////////
  // Write PWM speed to motor
  void setMotorPWM(int speed) {
    speed = constrain(speed * drive_dir, -PWMResolutionMaxValue, PWMResolutionMaxValue);

    if (speed > 0) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      ledcWrite(motorPWM, abs(speed));
    } else if (speed < 0) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      ledcWrite(motorPWM, abs(speed));
    } else stopMotor();
  }
  void stopMotor() {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, HIGH);
    ledcWrite(motorPWM, 0);
  }

  /////////////////////// Motor RPM control //////////////////
  // Feedforward - https://youtu.be/qKoPRacXk9Q?si=ahXkdiADK6ndN237
  // int feedForward_Control(double velocity, double acceleration) {
  int feedForward_Control(double velocity) {
    double acceleration = (velocity - prev_FF_velocity)*motor_update_interval/1000;
    int pwm_FF = FF_K_offset + FF_K_velocity * velocity + FF_K_accel * acceleration;
    return pwm_FF;
  }

  // PID feedback
  int PID_Control(double target_velocity = 0, double current_distance_change = 0) {
    double increment = target_velocity *motor_update_interval/1000;
    // double increment = 0 ;
    m_fwd_error += increment - current_distance_change;

    double diff = (m_fwd_error - m_previous_fwd_error);
    m_previous_fwd_error = m_fwd_error;

    int speed_PID_response = PID_Kp * m_fwd_error + PID_Kd * diff;

    return speed_PID_response;
  }

  // Combined speed signal
  void setSpeed(double target_velocity = 0) {
    // obtain speed from encoder

    unsigned long currentMillis = millis();
    if ((currentMillis - prevMillis) >= motor_update_interval) {
      double curr_distance = angle2mm();

      ////////////////////////// distance (mm) /////////////////////////////////////
      double time_elapsed = (currentMillis - prevMillis) / 1000.0;  // Convert ms to seconds
      double measured_distance_change = (curr_distance - prev_distance);
      measured_velocity = (curr_distance - prev_distance) / time_elapsed;  // mm/s

      prevMillis = currentMillis;
      prev_distance = curr_distance;

      // Apply feedforward and PID signal
      int PWM_signal = 0;
      // PWM_signal += feedForward_Control(target_velocity);
      PWM_signal += PID_Control(target_velocity, measured_distance_change);

      // // Print out debug velocities
      SerialBT.print(" ");
      SerialBT.print(currentMillis);
      SerialBT.print(" ");
      SerialBT.print(target_velocity);
      SerialBT.print(" ");
      SerialBT.print(measured_velocity);
      SerialBT.print(" ");
      SerialBT.print(PWM_signal);
      SerialBT.println();



      setMotorPWM(PWM_signal);
    }
  }


  void resetPID() {
    integral_error = 0;
    prev_error = 0;
    previous_measurement = 0;

    m_fwd_error = 0;
    m_previous_fwd_error = 0;
  }

  //////////////////////////////////////////////// Velocity profile //////////////////////////////////////////////////////////////////


  MotionParameters calculateTrapezoidalProfile(float distance, float max_velocity, float max_acceleration) {
    /*
          This function sets up the Trapezoidal velocity profile by calculating the shape of the graph by using the distance, max_velocity and max_acceleration
          assumption:
          1) acceleration and deceleration is equal (time for accel and decel are the same)
          2) 3 zones are available, Accel Zone, Steady State Zone, Decel Zone
          3) when possible, it will form trapezoidal profile, else it will reach as high velocity as it can before decel (triangle profile)
          4) Start and End velocities are 0

          case 1 (triangle): if distance is less than area needed for both accel and decel
          case 2 (trapezoidal): when enough area for accel and decel, add max velocity period in middle, as steady state zone
      */

    MotionParameters motionParams;
    motionParams.s_req = distance;
    if (max_acceleration > MAX_ACCELERATION)
      max_acceleration = MAX_ACCELERATION;
    if (max_velocity > MAX_VELOCITY)
      max_velocity = MAX_VELOCITY;

    motionParams.velocity = max_velocity;
    motionParams.acceleration = max_acceleration;

    motionParams.Vm = sqrt(motionParams.s_req * max_acceleration);
    if (motionParams.Vm <= max_velocity) {
      motionParams.ta = motionParams.Vm / max_acceleration;
      motionParams.T = 2 * motionParams.ta;
      motionParams.tc = 0;
      motionParams.tcf = 0;
    } else {
      motionParams.ta = max_velocity / max_acceleration;
      motionParams.tc = motionParams.s_req / max_velocity - motionParams.ta;
      motionParams.T = 2 * motionParams.ta + motionParams.tc;
      motionParams.tcf = motionParams.T - motionParams.ta;
    }

    // Convert to ms, since we use millis() function to compare time
    motionParams.T *= 1000;
    motionParams.ta *= 1000;
    motionParams.tc *= 1000;
    motionParams.tcf *= 1000;

    // Serial.print(motionParams.velocity);
    // Serial.print("  ");
    // Serial.print(motionParams.acceleration);
    // Serial.print("  ");
    // Serial.print(motionParams.T);
    // Serial.print("  ");
    // Serial.print(motionParams.ta);
    // Serial.print("  ");
    // Serial.print(motionParams.tc);
    // Serial.print("  ");
    // Serial.print(motionParams.Vm);
    // Serial.println("  ");

    // motionParams.velocity = max_velocity;
    // motionParams.acceleration = max_acceleration;

    motionParams.prev_time = millis();
    motionParams.time_step = 0;
    return motionParams;
  }

  float current_timestep_velocity = 0;
  float current_timestep_acceleration = 0;
  void followProfile(MotionParameters *motionParams) {
    /*
        This function implements the motion profile, and calculates the velocity and acceleration
        required at each timestep
        
        The first if statement is there so that we do a control action every fixed amount of seconds
        it enters the if statement every 2ms or watever we set.
        
        Once the duration of the control is over ie reached the end there is an additional leyway for
        pid to settle any remaining error, but as of now there is no need for such.
    
        In addition, the motion profile takes into account the maximum the motor can do, so the PID
        wont be requested a "harsh step", rather a gentler slope to follow.
    */
    unsigned long currentTime = millis();
    if ((currentTime - motionParams->prev_time) >= motor_update_interval) {
      motionParams->prev_time = currentTime;

      // Serial.print(motionParams->time_step);
      // Serial.print("  ");
      // Serial.print(motionParams->T*1000);
      // Serial.println("  ");

      if (motionParams->time_step <= motionParams->T) {

        // Acceleration Zone
        if (motionParams->time_step < motionParams->ta) {
          current_timestep_velocity = motionParams->acceleration * (motionParams->time_step / 1000);
          current_timestep_acceleration = motionParams->acceleration;

          // // Overshooting condition
          // } else if (motionParams->Vm <= motionParams->velocity){
          //     current_timestep_velocity = motionParams->Vm - motionParams->acceleration * ((motionParams->time_step/1000) - (motionParams->ta/1000));
          //     current_timestep_acceleration = -motionParams->acceleration;

          // Steady State Zone
        } else if ((motionParams->time_step >= motionParams->ta) && (motionParams->time_step <= motionParams->tcf)) {
          current_timestep_velocity = motionParams->velocity;
          current_timestep_acceleration = 0;

          // Deceleration Zone
        } else if (motionParams->time_step > motionParams->tcf) {

          current_timestep_velocity = motionParams->velocity - ((motionParams->time_step / 1000) - (motionParams->tcf / 1000)) * motionParams->acceleration;
          current_timestep_acceleration = -motionParams->acceleration;
        }

        // Update the control blocks with new control signals.
        motionParams->time_step += motor_update_interval;
        // Serial.print(current_timestep_velocity);
        // Serial.print("  ");
        // Serial.print(current_timestep_acceleration);
        // Serial.println("  ");
        setSpeed(current_timestep_velocity);

      } else {
        // To reach here we have passed the full duration of the feed forward action, we can stop the motor now.
        stopMotor();
      }
    }
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

// motor config
MotorControl leftMotor(
  4,    // motorPin1
  2,    // motorPin2
  15,   // motorPWM
  Wire  // I2C bus for encoder
);

MotorControl rightMotor(
  16,    // motorPin1
  17,    // motorPin2
  5,     // motorPWM
  Wire1  // I2C bus for encoder
);


const float FWD_KM = 260;  // mm/s/V
const float FWD_TM = 0.020;  // forward time constant (in seconds)
// const float FWD_TM = 0.07;  // forward time constant
// const float ROT_KM = 775.0;  // deg/s/Volt
// const float ROT_TM = 0.210;  // rotation time constant

// forward motion controller constants
// const float FWD_ZETA = 1.0;
const float FWD_ZETA = 0.707;
const float FWD_TD = FWD_TM;




void generateStepAtPWM(int pwm) {

  leftMotor.setMotorPWM(pwm);
  rightMotor.setMotorPWM(pwm);

  static unsigned long startMillis = 0;
  static unsigned long prevMillis = 0;
  startMillis = millis();
  unsigned long currentMillis = millis();
  do {
    currentMillis = millis();
    if ((currentMillis - prevMillis) >= 5) {
      SerialBT.print(" ");
      SerialBT.print(currentMillis);
      SerialBT.print(" ");
      SerialBT.print(leftMotor.angle2mm());
      SerialBT.print(" ");
      SerialBT.print(rightMotor.angle2mm());
      SerialBT.println();
      prevMillis = currentMillis;
    }


    // startMillis = currentMillis ;
  } while ((currentMillis - startMillis) <= 2000);
}
void generateStepResponse() {

  leftMotor.resetPID();
  rightMotor.resetPID();

  generateStepAtPWM(4095);
  generateStepAtPWM(3072);
  generateStepAtPWM(2048);
  generateStepAtPWM(1024);
  generateStepAtPWM(0);

  leftMotor.setMotorPWM(0);
  rightMotor.setMotorPWM(0);
}



void motor_subsystem_setup() {
  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);

  leftMotor.setupEncoder(1);  //set Counter_clockwise rotation
  leftMotor.setupMotor(1);

  rightMotor.setupEncoder(0);  //set Clockwise rotation
  rightMotor.setupMotor(1);

  //////////////////////////////////////////////////
  leftMotor.FF_K_offset = 380;
  leftMotor.FF_K_velocity = 3.72;
  leftMotor.FF_K_accel = (FWD_TM / leftMotor.FF_K_velocity );

  leftMotor.PID_Kp = 16 * FWD_TM / (FWD_KM  * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);

  // leftMotor.PID_Kp = FWD_TM / (FWD_KM  * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  // leftMotor.PID_Kp = 32 / (FWD_KM *FWD_TM);
  // Serial.print("leftMotor.PID_Kp  ");
  // Serial.println(leftMotor.PID_Kp);
  // leftMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / (FWD_KM  * FWD_TD);

  //////////////////////////////////////////////////
  rightMotor.FF_K_offset = 380;
  rightMotor.FF_K_velocity = 3.72;
  rightMotor.FF_K_accel = (FWD_TM / rightMotor.FF_K_velocity );

  // rightMotor.PID_Kp = 16 * FWD_TM / (FWD_KM  * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  // rightMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / (FWD_KM  * FWD_TD);
}