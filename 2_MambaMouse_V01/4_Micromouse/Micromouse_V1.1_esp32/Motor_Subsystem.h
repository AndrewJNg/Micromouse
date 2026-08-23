// https://github.com/curiores/ArduinoTutorials/tree/main
// BasicFilter -> ArduinoImplementations -> LowPass -> LowPass2.0

template<int order>  // order is 1 or 2
class LowPass {
private:
  float a[order];
  float b[order + 1];
  float omega0;
  float dt;
  bool adapt;
  float tn1 = 0;
  float x[order + 1];  // Raw values
  float y[order + 1];  // Filtered values

public:
  LowPass(float f0, float fs, bool adaptive) {
    // f0: cutoff frequency (Hz)
    // fs: sample frequency (Hz)
    // adaptive: boolean flag, if set to 1, the code will automatically set
    // the sample frequency based on the time history.

    omega0 = 6.28318530718 * f0;
    dt = 1.0 / fs;
    adapt = adaptive;
    tn1 = -dt;
    for (int k = 0; k < order + 1; k++) {
      x[k] = 0;
      y[k] = 0;
    }
    setCoef();
  }

  void setCoef() {
    if (adapt) {
      float t = micros() / 1.0e6;
      dt = t - tn1;
      tn1 = t;
    }

    float alpha = omega0 * dt;
    if (order == 1) {
      a[0] = -(alpha - 2.0) / (alpha + 2.0);
      b[0] = alpha / (alpha + 2.0);
      b[1] = alpha / (alpha + 2.0);
    }
    if (order == 2) {
      float alphaSq = alpha * alpha;
      float beta[] = { 1, sqrt(2), 1 };
      float D = alphaSq * beta[0] + 2 * alpha * beta[1] + 4 * beta[2];
      b[0] = alphaSq / D;
      b[1] = 2 * b[0];
      b[2] = b[0];
      a[0] = -(2 * alphaSq * beta[0] - 8 * beta[2]) / D;
      a[1] = -(beta[0] * alphaSq - 2 * beta[1] * alpha + 4 * beta[2]) / D;
    }
  }

  float filt(float xn) {
    // Provide me with the current raw value: x
    // I will give you the current filtered value: y
    if (adapt) {
      setCoef();  // Update coefficients if necessary
    }
    y[0] = 0;
    x[0] = xn;
    // Compute the filtered values
    for (int k = 0; k < order; k++) {
      y[0] += a[k] * y[k + 1] + b[k] * x[k];
    }
    y[0] += b[order] * x[order];

    // Save the historical values
    for (int k = order; k > 0; k--) {
      y[k] = y[k - 1];
      x[k] = x[k - 1];
    }

    // Return the filtered value
    return y[0];
  }
};


///////////////////////////////////////////////////////////////////////
#include <AS5600.h>  // https://github.com/RobTillaart/AS5600
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
#define motor_update_freq 200.0  // 100Hz -> update time -> 10ms

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
  AS5600 encoder;
  LowPass<1> lowPassFilter;

  // Motor properties
  byte motorPin1;
  byte motorPin2;
  byte motorPWM;
  byte motorChannel;
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
  double m_fwd_error=0;
  double m_previous_fwd_error =0;


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
  ///////////////////////////
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
  MotorControl(byte pin1, byte pin2, byte pwm, byte channel, TwoWire &wire)
    : motorPin1(pin1),
      motorPin2(pin2),
      motorPWM(pwm),
      motorChannel(channel),
      encoder(&wire),
      lowPassFilter(5, motor_update_freq, true) {}

  void setupEncoder(bool clockwise) {
    encoder.begin();
    encoder.setDirection(clockwise ? AS5600_COUNTERCLOCK_WISE : AS5600_CLOCK_WISE);
  }

  void setupMotor(int direction = 1) {
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    // ledcSetup(motorChannel, 5000, PWMResolution);
    // ledcAttachPin(motorPWM, motorChannel);
    ledcAttach(motorPWM, 5000, PWMResolution);

    stopMotor();
    drive_dir = (direction == 1 || direction == -1) ? direction : 1;  // Ensure drive_dir is either 1 or -1
    motor_update_interval = 1000 / motor_update_freq;                 //in ms
    PID_Kd = PID_Kd * motor_update_freq;
  }
  //////////////////////////////////////////////// Encoder feedback //////////////////////////////////////////////////////////////////
  // Encoder distance
  double updateEncoder() {
    /////////////////// Library cummulative calculation ///////////////
    double currAngle = encoder.getCumulativePosition(1);
    // return lowPassFilter.filt(currAngle);
    return currAngle;
  }

  double angle2mm() {
    return (2 * M_PI * wheelRadius * (double)updateEncoder()) / encoder_tick_per_rev;
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
  double feedForward_Control(double velocity, double acceleration) {
    double pwm_FF = FF_K_offset + FF_K_velocity * velocity + FF_K_accel * acceleration;
    return pwm_FF;
  }

  // PID feedback
  double PID_Control(double target_velocity = 0,double current_distance_change = 0) {
    double increment = target_velocity / motor_update_freq;
    // m_fwd_error -= current_distance_change;
    m_fwd_error = m_fwd_error + increment - current_distance_change;
  
    double diff = (m_fwd_error - m_previous_fwd_error );
    
    // Note (prev_error - err) has a large difference with changing setpoint, resulting in large Kd spikes
    // while (previos_measurement - current_measured_velocity) means it is difference on measurement, and would eliminate the Kd spike issue
    // double speed_PID_response = PID_Kp * m_fwd_error + PID_Ki * integral_error + PID_Kd * diff + PID_BIAS;
    double speed_PID_response = PID_Kp * m_fwd_error ;

      // SerialBT.print(increment);
    // integral_error += err;
    // prev_error = err;
    m_previous_fwd_error = m_fwd_error;
    // previous_measurement = current_distance_change;  // differentiate on derivative

    return speed_PID_response;
  }
  // double PID_Control(double target_velocity = 0, double measured_velocity = 0) {
  //   err = (target_velocity - measured_velocity);


  //   // Note (prev_error - err) has a large difference with changing setpoint, resulting in large Kd spikes
  //   // while (previos_measurement - current_measured_velocity) means it is difference on measurement, and would eliminate the Kd spike issue
  //   double speed_PID_response = PID_Kp * err + PID_Ki * integral_error + PID_Kd * (previous_measurement - measured_velocity) + PID_BIAS;

  //   integral_error += err;
  //   prev_error = err;
  //   previous_measurement = measured_velocity;  // differentiate on derivative

  //   // double pwm_PID_correction = speed_PID_response * FF_K_velocity;
  //   return speed_PID_response;
  // }

  // Combined speed signal
  void setSpeed(double target_velocity = 0, double acceleration = 0) {
    // obtain speed from encoder

    unsigned long currentMillis = millis();
    if ((currentMillis - prevMillis) >= motor_update_interval)  {
      double curr_distance = angle2mm();
      ////////////////////////// distance (mm) /////////////////////////////////////
      double time_elapsed = (currentMillis - prevMillis) / 1000.0;  // Convert ms to seconds
      double measured_distance_change = (curr_distance - prev_distance);
      measured_velocity = (curr_distance - prev_distance) / time_elapsed;     // mm/s

      // if (measured_velocity <= abs(10)) 
      // {
        // return;
      //   SerialBT.print("Exit ");
      //   // measured_velocity = prev_velocity;
      //   SerialBT.print(measured_velocity);
      // }
      // else {
      //   // prev_velocity = measured_velocity;
      //   SerialBT.print("Enter ");
      //   SerialBT.print(measured_velocity);
      //   // prev_distance = curr_distance;
      //   prev_velocity_Millis = currentMillis;
      //   prev_distance = curr_distance;
      //   // prev_velocity = measured_velocity ;
      // }
      prevMillis = currentMillis;
      prev_distance = curr_distance;



      ////////////////////////// RPM /////////////////////////////////////
      // double curr_distance = updateEncoder();
      // double time_elapsed = (currentMillis - prevMillis) / 1000.0; // Convert ms to seconds
      // measured_velocity = (60*(curr_distance - prev_distance) )/ (time_elapsed*4096); // mm/s

      //////////////////////////////////////////////////////////////////////////////
      // Serial.print("time: ");
      // Serial.print(currentMillis);
      // Serial.print("prev: ");
      // Serial.print(prevMillis);

      // Serial.print("curr: ");
      // Serial.print(curr_distance);
      // Serial.print("prev: ");
      // Serial.print(prev_distance);

      // Serial.print("  Speed: ");
      // Serial.println(measured_velocity);




      // Apply feedforward and PID signal
      double PWM_signal = 0;
      // PWM_signal += feedForward_Control(target_velocity, acceleration);
      // PWM_signal += PID_Control(target_velocity, measured_velocity);
      
      // double FF_n_PID_velocity = 0;

      // FF_n_PID_velocity += target_velocity;
      // FF_n_PID_velocity += PID_Control(target_velocity, measured_velocity);

      // PWM_signal += feedForward_Control(target_velocity, acceleration);
      // PWM_signal += PID_Control(target_velocity, measured_velocity);  // compare position, instead of velocity
      
      // double target_distance = abs(target_velocity*motor_update_interval) + curr_distance;
      PWM_signal += PID_Control(target_velocity, measured_distance_change);  // compare position, instead of velocity

      SerialBT.print(" ");
      SerialBT.print(currentMillis);
      SerialBT.print(" ");
      // SerialBT.print(target_distance);
      SerialBT.print(target_velocity);
      SerialBT.print(" ");
      // SerialBT.print(curr_distance);
      SerialBT.print(measured_velocity);
      // SerialBT.print(" ");
      // SerialBT.print(PWM_signal);
      SerialBT.println();



      setMotorPWM(PWM_signal);
      
    }
  }


  void resetPID() {
    integral_error = 0;
    prev_error = 0;
    previous_measurement = 0;
    
    m_fwd_error= angle2mm();
    m_previous_fwd_error =0;
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
        setSpeed(current_timestep_velocity, current_timestep_acceleration);

      } else {
        // To reach here we have passed the full duration of the feed forward action, we can stop the motor now.
        stopMotor();
      }
    }
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};



MotorControl leftMotor(
  4,    // motorPin1
  2,    // motorPin2
  15,   // motorPWM
  0,    // ESP32 motorChannel
  Wire  // I2C bus for encoder
);

MotorControl rightMotor(
  16,    // motorPin1
  17,    // motorPin2
  5,     // motorPWM
  1,     // ESP32 motorChannel
  Wire1  // I2C bus for encoder
);


const float FWD_KM = 475.0;  // mm/s/Volt
const float FWD_TM = 0.070;  // forward time constant
const float ROT_KM = 775.0;  // deg/s/Volt
const float ROT_TM = 0.210;  // rotation time constant

// forward motion controller constants
const float FWD_ZETA = 0.707;
const float FWD_TD = FWD_TM;


  // // Feed forward portion
  // const float SPEED_FF = (1.0 / FWD_KM);
  // const float ACC_FF = (FWD_TM / FWD_KM);
  // const float BIAS_FF = 0.121;


const float FWD_KP = 16 * FWD_TM / (FWD_KM * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
const float FWD_KD = motor_update_freq * (8 * FWD_TM - FWD_TD) / (FWD_KM * FWD_TD);



void motor_subsystem_setup() {
  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);

  leftMotor.setupEncoder(AS5600_COUNTERCLOCK_WISE);  //set Counter_clockwise rotation
  leftMotor.setupMotor(1);

  rightMotor.setupEncoder(AS5600_CLOCK_WISE);  //set Clockwise rotation
  rightMotor.setupMotor(1);
  
  //////////////////////////////////////////////////
  leftMotor.FF_K_offset = 239; 
  leftMotor.FF_K_velocity = 3.12; //mm per second per volt
  leftMotor.FF_K_accel = (FWD_TM / leftMotor.FF_K_velocity);

  leftMotor.PID_BIAS = 0;
  leftMotor.PID_Kp = 16 * FWD_TM / ( leftMotor.FF_K_velocity * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  leftMotor.PID_Ki = 0;
  leftMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / ( leftMotor.FF_K_velocity * FWD_TD);

  //////////////////////////////////////////////////
  rightMotor.FF_K_offset = 374;
  rightMotor.FF_K_velocity = 3.47;
  rightMotor.FF_K_accel = (FWD_TM / rightMotor.FF_K_velocity);

  rightMotor.PID_BIAS = 0;
  rightMotor.PID_Kp = 16 * FWD_TM / (rightMotor.FF_K_velocity * FWD_ZETA * FWD_ZETA * FWD_TD * FWD_TD);
  rightMotor.PID_Ki = 0;
  rightMotor.PID_Kd = motor_update_freq * (8 * FWD_TM - FWD_TD) / (rightMotor.FF_K_velocity * FWD_TD);
}
void generateStepAtPWM(int pwm) {

  leftMotor.setMotorPWM(pwm);
  rightMotor.setMotorPWM(pwm);

  static unsigned long startMillis = 0;
  static unsigned long prevMillis = 0;
  startMillis = millis();
  unsigned long currentMillis = millis();
  do {
    currentMillis = millis();
    if ((currentMillis - prevMillis) >= 10) {
      Serial.print(" ");
      Serial.print(currentMillis);
      Serial.print(" ");
      Serial.print(leftMotor.angle2mm());
      Serial.print(" ");
      Serial.print(rightMotor.angle2mm());
      Serial.println();

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
