///////////////////////////////////////////////////////////////////////
#include "MT6701.h"
#include <cmath>

// Encoder parameters
#define wheelRadius 17.0
#define MAX_ACCELERATION 3000  // mm/s/s
#define MAX_VELOCITY 2000      // mm/s

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
#define motor_update_freq 100.0  // 200Hz -> update time -> 5ms

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
  double prev_FF_velocity = 0;
  double target_pos =0;


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

  double current_batt_voltage = 0;
  ////////////////////////////////////////////// Setup ////////////////////////////////////////////////////////////////////
  MotorControl(byte pin1, byte pin2, TwoWire &wire)
    : motorPin1(pin1),
      motorPin2(pin2){
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
    // pinMode(motorPin1, OUTPUT);
    // pinMode(motorPin2, OUTPUT);
    ledcAttach(motorPin1, 5000, PWMResolution);
    ledcAttach(motorPin2, 5000, PWMResolution);

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
      ledcWrite(motorPin1, 0);
      ledcWrite(motorPin2, abs(speed));

    } else if (speed < 0) {
      ledcWrite(motorPin1, abs(speed));
      ledcWrite(motorPin2, 0);
      
    } else stopMotor();
  }
  void setMotorVolt(double Volt) {

    // Volt = constrain(Volt, -current_batt_voltage, current_batt_voltage);
    int pwm = map(Volt*100, -current_batt_voltage*100, current_batt_voltage*100, -PWMResolutionMaxValue, PWMResolutionMaxValue);

    setMotorPWM(pwm);
  }

  void stopMotor() {
      ledcWrite(motorPin1, 0);
      ledcWrite(motorPin2, 0);
  }

  /////////////////////// Motor RPM control //////////////////
  // Feedforward - https://youtu.be/qKoPRacXk9Q?si=ahXkdiADK6ndN237
  // int feedForward_Control(double velocity, double acceleration) {
  double feedForward_Control(double velocity) {
    double acceleration = (velocity - prev_FF_velocity) * motor_update_interval / 1000.0;
    double pwm_FF = FF_K_offset + FF_K_velocity * velocity + FF_K_accel * acceleration;
    return pwm_FF;
  }

  // // PID feedback
  // double PID_Control(double target_velocity = 0, double current_distance_change = 0) {
  //   double increment = target_velocity * motor_update_interval / 1000.0;
  //   // double increment = 0 ;
  //   m_fwd_error += increment - current_distance_change;

  //   double diff = (m_fwd_error - m_previous_fwd_error);
  //   m_previous_fwd_error = m_fwd_error;

  //   double speed_PID_response = PID_Kp * m_fwd_error + PID_Kd * diff;
    
  //     // // Print out debug velocities
  //     SerialBT.print(" ");
  //     SerialBT.print(millis());
  //     SerialBT.print(" ");
  //     SerialBT.print(increment);
  //     SerialBT.print(" ");
  //     SerialBT.print(m_fwd_error);
  //     SerialBT.print(" ");
  //     SerialBT.print(speed_PID_response);
  //     SerialBT.println();

  //   return speed_PID_response;
  // }
    // PID feedback
  double PID_Control(double target_pos = 0, double current_pos = 0) {
    // double increment = target_velocity * motor_update_interval / 1000.0;
    // double increment = 0 ;
    m_fwd_error = target_pos - current_pos;

    double diff = (m_fwd_error - m_previous_fwd_error);
    m_previous_fwd_error = m_fwd_error;

    double speed_PID_response = PID_Kp * m_fwd_error + PID_Kd * diff;
    
      // // Print out debug velocities
      // SerialBT.print(" ");
      // SerialBT.print(millis());
      // SerialBT.print(" ");
      // SerialBT.print(target_pos);
      // SerialBT.print(" ");
      // SerialBT.print(current_pos);
      // SerialBT.print(" ");
      // SerialBT.print(speed_PID_response);
      // SerialBT.println();

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
      // double measured_distance_change = (curr_distance - prev_distance);
      measured_velocity = (curr_distance - prev_distance) / time_elapsed;  // mm/s

      prevMillis = currentMillis;
      prev_distance = curr_distance;

      // Apply feedforward and PID signal
      double Volt_signal = 0;
      // Volt_signal += feedForward_Control(target_velocity);
      
      target_pos += target_velocity * time_elapsed;
      Volt_signal += PID_Control(target_pos, curr_distance);

      // // Print out debug velocities
      SerialBT.print(" ");
      SerialBT.print(currentMillis);
      SerialBT.print(" ");
      SerialBT.print(target_velocity);
      SerialBT.print(" ");
      SerialBT.print(measured_velocity);
      SerialBT.print(" ");
      SerialBT.print(Volt_signal);
      SerialBT.println();


      setMotorVolt(Volt_signal);
    }
  }


  void resetPID() {
    integral_error = 0;
    prev_error = 0;
    previous_measurement = 0;

    m_fwd_error = 0;
    m_previous_fwd_error = 0;
    target_pos=angle2mm();
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
      motionParams.ta = sqrt(motionParams.s_req / max_acceleration);
      motionParams.T = 2 * motionParams.ta;
      motionParams.tc = 0;
      motionParams.tcf = motionParams.ta ;
      
    SerialBT.println("triangle");
    } else {

      motionParams.Vm = max_velocity;
      motionParams.ta = max_velocity / max_acceleration;
      motionParams.tc = motionParams.s_req / max_velocity - motionParams.ta;
      motionParams.T = 2 * motionParams.ta + motionParams.tc;
      motionParams.tcf = motionParams.T - motionParams.ta;
    SerialBT.println("tarpezoidal");
    }

    // Convert to ms, since we use millis() function to compare time
    motionParams.T *= 1000;
    motionParams.ta *= 1000;
    motionParams.tc *= 1000;
    motionParams.tcf *= 1000;


    SerialBT.print("s:");
    SerialBT.print( motionParams.s_req );
    SerialBT.print("  vel:");
    SerialBT.print(motionParams.velocity);
    SerialBT.print("  accel:");
    SerialBT.print(motionParams.acceleration);
    SerialBT.print("  Total Time:");
    SerialBT.print(motionParams.T);
    SerialBT.print("  Ta:");
    SerialBT.print(motionParams.ta);
    SerialBT.print("  Tc:");
    SerialBT.print(motionParams.tc);
    SerialBT.print("  Vm:");
    SerialBT.print(motionParams.Vm);
    SerialBT.println("  ");

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
      
      motionParams->time_step += (currentTime - motionParams->prev_time);
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
    // SerialBT.println("  Accel");

          // Steady State Zone
        } else if ((motionParams->time_step >= motionParams->ta) && (motionParams->time_step <= motionParams->tcf)) {
          current_timestep_velocity = motionParams->velocity;
          current_timestep_acceleration = 0;
    // SerialBT.println("  Steady");

          // Deceleration Zone
        } else if (motionParams->time_step > motionParams->tcf) {

          current_timestep_velocity = motionParams->Vm - ((motionParams->time_step / 1000) - (motionParams->tcf / 1000)) * motionParams->acceleration;
          current_timestep_acceleration = -motionParams->acceleration;
    // SerialBT.println("  Decel");
        }

        // Update the control blocks with new control signals.
        // motionParams->time_step += motor_update_interval;
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
  2,    // motorPin1
  4,    // motorPin2
  Wire  // I2C bus for encoder
);

MotorControl rightMotor(
  17,    // motorPin1
  16,    // motorPin2
  Wire1  // I2C bus for encoder
);


const float FWD_KM = 52.0;  // mm/s/V
const float FWD_TM = 0.105;  // forward time constant (in seconds)
const float FWD_TD = 6*FWD_TM;
// const float FWD_TM = 0.020;  // forward time constant (in seconds)
// const float FWD_TD = 6*FWD_TM;


// const float FWD_TM = 0.07;  // forward time constant
// const float ROT_KM = 775.0;  // deg/s/Volt
// const float ROT_TM = 0.210;  // rotation time constant

// forward motion controller constants
// const float FWD_ZETA = 1.0;
const float FWD_ZETA = 0.707;
// const float FWD_TD = 6*FWD_TM;
// const float FWD_TD = FWD_TM;




void generateStepAtVolt(int Volt) {

  leftMotor.setMotorVolt(Volt);
  rightMotor.setMotorVolt(Volt);

  static unsigned long startMillis = 0;
  static unsigned long prevMillis = 0;
  startMillis = millis();
  unsigned long currentMillis = millis();
  do {
    currentMillis = millis();
    if ((currentMillis - prevMillis) >= 10) {
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

  generateStepAtVolt(8);
  generateStepAtVolt(6);
  generateStepAtVolt(4);
  generateStepAtVolt(0);

  leftMotor.setMotorVolt(0);
  rightMotor.setMotorVolt(0);
}



void motor_subsystem_setup() {
  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);

  leftMotor.setupEncoder(1);  //set Counter_clockwise rotation
  leftMotor.setupMotor(1);

  rightMotor.setupEncoder(0);  //set Clockwise rotation
  rightMotor.setupMotor(1);

  //////////////////////////////////////////////////
  leftMotor.FF_K_offset = 0.264;
  leftMotor.FF_K_velocity = 1.0 / FWD_KM;
  leftMotor.FF_K_accel = (FWD_TM / FWD_KM);

  leftMotor.PID_Kp = 16 * FWD_TM / (FWD_KM * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  leftMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / (FWD_KM * FWD_TD);

  // leftMotor.PID_Kp = FWD_TM / (FWD_KM  * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  // leftMotor.PID_Kp = 32 / (FWD_KM *FWD_TM);
  // Serial.print("leftMotor.PID_Kp  ");
  // Serial.println(leftMotor.PID_Kp);
  // leftMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / (FWD_KM  * FWD_TD);

  //////////////////////////////////////////////////
  rightMotor.FF_K_offset = 0.264;
  rightMotor.FF_K_velocity = 1.0 / FWD_KM;
  rightMotor.FF_K_accel = (FWD_TM / FWD_KM);

  rightMotor.PID_Kp = 16 * FWD_TM / (FWD_KM  * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  rightMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / (FWD_KM  * FWD_TD);
}