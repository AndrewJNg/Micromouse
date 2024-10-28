#include <AS5600.h>  // https://github.com/RobTillaart/AS5600
#include <cmath>
#include "lowPass.h"

// Encoder parameters
#define wheelRadius 17.0
#define MAX_ACCELERATION 1000 // mm/s/s
#define MAX_VELOCITY     1000 // mm/s

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
#define motor_update_freq 100  // 100Hz -> update time -> 10ms

typedef struct MotionParameters{
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

  //low pass filter at 5Hz, sample at 100Hz
  LowPass<1> lowPassFilter;

  // Encoder properties
  int currAngle = 0;
  int prevAngle = 0;
  int multiplyAngle = 0;
  byte isclockwise;

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
  double curr_distance = 0;
  

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
    isclockwise = clockwise;
    encoder.setDirection(clockwise ? AS5600_COUNTERCLOCK_WISE : AS5600_CLOCK_WISE);
  }

  void setupMotor(int direction = 1) {
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    ledcSetup(motorChannel, 5000, PWMResolution);
    ledcAttachPin(motorPWM, motorChannel);
    stopMotor();
    drive_dir = (direction == 1 || direction == -1) ? direction : 1;  // Ensure drive_dir is either 1 or -1
    motor_update_interval = 1000 / motor_update_freq;                 //in ms
    PID_Kd = PID_Kd * motor_update_freq;
  }
  //////////////////////////////////////////////// Encoder feedback //////////////////////////////////////////////////////////////////
  // Encoder distance
  double updateEncoder() {
    /////////////////// Library cummulative calculation ///////////////
    currAngle = encoder.getCumulativePosition(1);
    return lowPassFilter.filt(currAngle);
    // return currAngle;
  }

  double angle2mm() {
    return (2 * M_PI * wheelRadius * (double)updateEncoder()) / encoder_tick_per_rev;
  }

  //////////////////////////////////////////////// Motor control //////////////////////////////////////////////////////////////////
  // Write PWM speed to motor
  void setMotorPWM(int speed) {
    speed = constrain(speed * drive_dir, -PWMResolutionMaxValue, PWMResolutionMaxValue);
    if (speed > 0) 
    {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      ledcWrite(motorChannel, abs(speed));
    }
    else if (speed < 0) 
    {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      ledcWrite(motorChannel, abs(speed));
    }
    else stopMotor();
  }
  void stopMotor()
  {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, HIGH);
      ledcWrite(motorChannel, 0);

  }

  /////////////////////// Motor RPM control //////////////////
  // Feedforward - https://youtu.be/qKoPRacXk9Q?si=ahXkdiADK6ndN237
  double feedForward_Control(double velocity, double acceleration) {
    double pwm_FF = FF_K_offset + FF_K_velocity * velocity + FF_K_accel * acceleration;
    return pwm_FF;
  }

  // PID feedback
  double PID_Control(double target_velocity = 0, double measured_velocity = 0) {
    err = (target_velocity - measured_velocity);

    // Note (prev_error - err) has a large difference with changing setpoint, resulting in large Kd spikes
    // while (previos_measurement - current_measured_velocity) means it is difference on measurement, and would eliminate the Kd spike issue
    double pwm_PID = PID_Kp * err + PID_Ki * integral_error + PID_Kd * (previous_measurement - measured_velocity) + PID_BIAS;

    integral_error += err;
    prev_error = err;
    previous_measurement = measured_velocity;  // differentiate on derivative

    return pwm_PID;
  }

  // Combined speed signal
  void setSpeed(double target_velocity = 0, double acceleration = 0) {
    // obtain speed from encoder

    unsigned long currentMillis = millis();

    if (currentMillis - prevMillis >= motor_update_interval) {

      ////////////////////////// distance (mm) /////////////////////////////////////
      curr_distance = angle2mm();
      double time_elapsed = (currentMillis - prevMillis) / 1000.0;         // Convert ms to seconds
      measured_velocity = (curr_distance - prev_distance) / time_elapsed;  // mm/s

      ////////////////////////// RPM /////////////////////////////////////
      // curr_distance = updateEncoder();
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

      prevMillis = currentMillis;
      prev_distance = curr_distance;



      // Apply feedforward and PID signal
      double PWM_signal = 0;
      PWM_signal += feedForward_Control(target_velocity, acceleration);
      PWM_signal += PID_Control(target_velocity, measured_velocity);
      
      Serial.print(" ");
      Serial.print(currentMillis);
      // Serial.print(" ");
      // Serial.print(angle2mm());
      // Serial.print(" ");
      // Serial.print(angle2mm());
      // Serial.println();

      Serial.print(" ");
      Serial.print(target_velocity);
      Serial.print(" ");
      Serial.print(measured_velocity);
      // Serial.print(" ");
      // Serial.print(feedForward_Control(target_velocity, acceleration));
      // Serial.print(" ");
      // Serial.print(PWM_signal);
      Serial.println();

      setMotorPWM(PWM_signal);
    }
  }


  void resetPID() {
    integral_error = 0;
    prev_error = 0;
    previous_measurement = 0;
  }
  
  //////////////////////////////////////////////// Velocity profile //////////////////////////////////////////////////////////////////
  

  MotionParameters calculateTrapezoidalProfile(float distance, float max_velocity, float max_acceleration) {
      /*
          This function sets up the Trapezoidal velocity profile by calculating the shape of the graph by using the distance, max_velocity and max_acceleration
          assumption:
          1) acceleration and deceleration is equal (time for accel and decel are the same)
          2) when possible, it will reach max_velocity (trapezoidal profile), else it will reach as high as it can before decel (triangle profile)
          3) 

          case 1 (triangle): if distance is less than area needed for both accel and decel
          case 2 (trapezoidal): when enough area for accel and decel, add period at max velocity in middle
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
      if (motionParams.Vm <= max_velocity){
          motionParams.ta = motionParams.Vm / max_acceleration;
          motionParams.T = 2 * motionParams.ta;
          motionParams.tc = 0;
          motionParams.tcf = 0;
      }else{
          motionParams.ta = max_velocity / max_acceleration;
          motionParams.tc = motionParams.s_req / max_velocity - motionParams.ta;
          motionParams.T = 2 * motionParams.ta + motionParams.tc;
          motionParams.tcf = motionParams.T - motionParams.ta;
      }
      // Convert to ms, since we use millis() function to compare time
      motionParams.T*=1000;
      motionParams.ta*=1000;
      motionParams.tc*=1000;
      motionParams.tcf*=1000;

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
  void followProfile(MotionParameters *motionParams){
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
    if ( (currentTime - motionParams->prev_time) >=  motor_update_interval){
        motionParams->prev_time = currentTime;

      // Serial.print(motionParams->time_step);
      // Serial.print("  ");
      // Serial.print(motionParams->T*1000);
      // Serial.println("  ");

        if (motionParams->time_step <= (motionParams->T+ motor_update_interval * 0)){
            if (motionParams->time_step < motionParams->ta){
                current_timestep_velocity = motionParams->acceleration * (motionParams->time_step/1000);
                current_timestep_acceleration = motionParams->acceleration;
            } else if (motionParams->Vm <= motionParams->velocity){
                current_timestep_velocity = motionParams->Vm - motionParams->acceleration * ((motionParams->time_step/1000) - (motionParams->ta/1000));
                current_timestep_acceleration = -motionParams->acceleration;
            } else if ((motionParams->time_step >= motionParams->ta) && (motionParams->time_step <= motionParams->tcf)){
                current_timestep_velocity = motionParams->velocity;
                current_timestep_acceleration = 0;
            } else if (motionParams->time_step > motionParams->tcf){
                current_timestep_velocity = motionParams->velocity - ((motionParams->time_step/1000) - (motionParams->tcf/1000)) * motionParams->acceleration;
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

void motor_subsystem_setup() {
  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);

  leftMotor.setupEncoder(AS5600_COUNTERCLOCK_WISE);  //set Counter_clockwise rotation
  leftMotor.setupMotor(1);

  rightMotor.setupEncoder(AS5600_CLOCK_WISE);  //set Clockwise rotation
  rightMotor.setupMotor(1);

  double Td = 0.05;
  // Tm = 0.03
  // Km = 3.57
  leftMotor.Tm = 0.035;
  leftMotor.FF_K_offset = 64.2;
  leftMotor.FF_K_velocity = 3.97;
  // leftMotor.FF_K_accel = 4096*leftMotor.Tm;  //max voltage over max acceleration, accel = 1/tau

  leftMotor.PID_BIAS = 0;
  leftMotor.PID_Kp = 7.80;// (leftMotor.Tm * 64.0) / (leftMotor.FF_K_velocity * (double)sqrt(2.0)*sqrt(2.0) * Td * Td);
  // leftMotor.PID_Kp = KpLeft;
  leftMotor.PID_Ki = 0;
  leftMotor.PID_Kd = 0.04;//(8 * leftMotor.Tm - Td) / (Td * leftMotor.FF_K_velocity);

  //////////////////////////////////////////////////
  // Tm = 0.03
  // Km = 4.08
  rightMotor.Tm = 0.035;
  rightMotor.FF_K_offset = 784;
  rightMotor.FF_K_velocity = 4.05;
  // rightMotor.FF_K_accel = 4096*leftMotor.Tm;  //max voltage over max acceleration, accel = 1/tau

  rightMotor.PID_BIAS = 0;
  rightMotor.PID_Kp = 7.8;//(rightMotor.Tm*32.0) / (rightMotor.FF_K_velocity * (double) sqrt(2.0) * Td* Td) ;
  // rightMotor.PID_Kp = 0;
  rightMotor.PID_Ki = 0;
  // rightMotor.PID_Kd = 0;
  rightMotor.PID_Kd = 0.04; //(8 * rightMotor.Tm - Td ) / (Td*rightMotor.FF_K_velocity);
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
      // curr_distance =
      Serial.print(" ");
      Serial.print(currentMillis);
      Serial.print(" ");
      Serial.print(leftMotor.angle2mm());
      Serial.print(" ");
      Serial.print(rightMotor.angle2mm());
      Serial.println();

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
