#include <AS5600.h>  // https://github.com/RobTillaart/AS5600
#include <cmath>
#include "lowPass.h"

// Encoder parameters
#define wheelRadius 17.0
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
#define motor_update_freq 100 // 100Hz -> update time -> 10ms 

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
    int drive_dir = 1; // 1 for normal, -1 for inverted direction setup
    
    // System setup
    int motor_update_interval =0; // matches motor_update_freq in time interval (updated in setup)


    double integral_error = 0;
    double prev_error = 0;
    double previous_measurement = 0;
    
    unsigned long prevMillis = 0;
    
    double prev_distance = 0;
    double curr_distance = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
    ///////////////////////////
    // Feedforward constants
    double FF_K_offset = 100;
    double FF_K_velocity = 8;
    double FF_K_accel = 0;
    
    ///////////////////////////
    // PID constants
    double PID_BIAS =0;
    double PID_Kp =0;
    double PID_Ki = 0;
    double PID_Kd =0;

    double err = 0;
    double measured_velocity=0;

    MotorControl(byte pin1, byte pin2, byte pwm, byte channel, TwoWire &wire)
      : motorPin1(pin1), 
        motorPin2(pin2), 
        motorPWM(pwm), 
        motorChannel(channel), 
        encoder(&wire),
        lowPassFilter(5, motor_update_freq, true)
        {}

    void setupEncoder(bool clockwise) {
        encoder.begin();
        isclockwise = clockwise;
        encoder.setDirection(clockwise ? AS5600_COUNTERCLOCK_WISE: AS5600_CLOCK_WISE );
    }

    void setupMotor(int direction = 1) {
        pinMode(motorPin1, OUTPUT);
        pinMode(motorPin2, OUTPUT);
        ledcSetup(motorChannel, 5000, PWMResolution);
        ledcAttachPin(motorPWM, motorChannel);
        stopMotor();
        drive_dir = (direction == 1 || direction == -1) ? direction : 1; // Ensure drive_dir is either 1 or -1
        motor_update_interval = 1000 /motor_update_freq; //in ms
        PID_Kd = PID_Kd * motor_update_freq;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Encoder distance
    double updateEncoder() {
        /////////////////// Manual cummulative calculation ///////////////
        // currAngle = encoder.readAngle();

        // if (prevAngle >= 3072 && currAngle <= 1024) multiplyAngle++;
        // else if (prevAngle <= 1024 && currAngle >= 3072) multiplyAngle--;

        // prevAngle = currAngle;
        // currAngle += multiplyAngle * 4096;

        /////////////////// Library cummulative calculation ///////////////
        currAngle = encoder.getCumulativePosition(1);
        return lowPassFilter.filt(currAngle);
    }

    double angle2mm(){
        return (2 * M_PI * wheelRadius * (double) updateEncoder()) / encoder_tick_per_rev;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Feedforward - https://youtu.be/qKoPRacXk9Q?si=ahXkdiADK6ndN237
    double feedForward_Control(double velocity, double acceleration){
          double pwm_FF = FF_K_offset + FF_K_velocity * velocity + FF_K_accel * acceleration;
          return pwm_FF;
    }

    // PID feedback
    double PID_Control(double target_velocity = 0, double measured_velocity = 0){
          err = (target_velocity - measured_velocity);

          // Note (prev_error - err) has a large difference with changing setpoint, resulting in large Kd spikes
          // while (previos_measurement - current_measured_velocity) means it is difference on measurement, and would eliminate the Kd spike issue
          double pwm_PID = PID_Kp * err + PID_Ki * integral_error + PID_Kd * (previous_measurement - measured_velocity) + PID_BIAS;
          
          integral_error += err;
          prev_error = err; 
          previous_measurement = measured_velocity; // differentiate on derivative

          return pwm_PID;
    }

    // Combined speed signal
    void setSpeed(double target_velocity = 0, double acceleration = 0){
        // obtain speed from encoder
        
        unsigned long currentMillis = millis();
  
        if (currentMillis - prevMillis >= motor_update_interval) {

            ////////////////////////// distance (mm) /////////////////////////////////////
            curr_distance = angle2mm();
            double time_elapsed = (currentMillis - prevMillis) / 1000.0; // Convert ms to seconds 
            measured_velocity = (curr_distance - prev_distance) / time_elapsed; // mm/s

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
            double PWM_signal =0;
            PWM_signal += feedForward_Control(target_velocity, acceleration);
            // PWM_signal += PID_Control(target_velocity, measured_velocity);

            setMotorPWM(PWM_signal);
        }

    }


    void resetPID(){
      integral_error = 0;
      prev_error = 0;
      previous_measurement = 0;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setMotorPWM(int speed) {
        speed = constrain(speed*drive_dir, -PWMResolutionMaxValue, PWMResolutionMaxValue);
        if (speed > 0) moveForward(abs(speed));
        else if (speed < 0) moveBackward(abs(speed));
        else stopMotor();
        
        updateEncoder();
    }
    
    void stopMotor() {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, HIGH);
        ledcWrite(motorChannel, 0);
    }

private:
    void moveForward(int speed) {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        ledcWrite(motorChannel, speed);
    }

    void moveBackward(int speed) {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        ledcWrite(motorChannel, speed);
    }

};



MotorControl leftMotor(
    4,   // motorPin1
    2,   // motorPin2
    15,  // motorPWM
    0,   // ESP32 motorChannel
    Wire // I2C bus for encoder
);

MotorControl rightMotor(
    16,   // motorPin1
    17,   // motorPin2
    5,  // motorPWM
    1,   // ESP32 motorChannel
    Wire1 // I2C bus for encoder
);

void motor_subsystem_setup() {
  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);

  leftMotor.setupEncoder(AS5600_COUNTERCLOCK_WISE);  //set Counter_clockwise rotation
  leftMotor.setupMotor(1);
    
  rightMotor.setupEncoder(AS5600_CLOCK_WISE);  //set Clockwise rotation
  rightMotor.setupMotor(1);

  
    // Tm = 0.03
    // Km = 3.57
    leftMotor.FF_K_offset = 218;
    leftMotor.FF_K_velocity = 3.57;
    leftMotor.FF_K_accel = 122.85; //max voltage over max acceleration
    
    leftMotor.PID_BIAS =0;
    leftMotor.PID_Kp =0;
    leftMotor.PID_Ki = 0;
    leftMotor.PID_Kd =0;

//////////////////////////////////////////////////
    // Tm = 0.03
    // Km = 4.08
    rightMotor.FF_K_offset = 364;
    rightMotor.FF_K_velocity = 4.08;
    rightMotor.FF_K_accel = 122.85; //max voltage over max acceleration
    
    rightMotor.PID_BIAS =0;
    rightMotor.PID_Kp =0;
    rightMotor.PID_Ki = 0;
    rightMotor.PID_Kd =0;

    

}
void generateStepAtPWM(int pwm)
{

  leftMotor.setMotorPWM(pwm);
  rightMotor.setMotorPWM(pwm);

  static unsigned long startMillis = 0;
  static unsigned long prevMillis = 0;
  startMillis = millis();
  unsigned long currentMillis = millis();
  do {
    currentMillis = millis();
    if((currentMillis - prevMillis)>=1)
    {
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
  }while((currentMillis - startMillis) <= 500);

}
void generateStepResponse(){
  
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
