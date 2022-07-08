/********************************************************
   PID Basic Example
   Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

//#define PIN_INPUT 0
//#define PIN_OUTPUT 3

//Define Variables we'll be connecting to

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
PID leftMotorVel(&InputRpmLeft, &OutputLeftMotor, &rpmSetLeft, Kp, Ki, Kd, DIRECT);
PID rightMotorVel(&InputRpmRight, &OutputRightMotor, &rpmSetRight, Kp, Ki, Kd, DIRECT);

void PID_setup()
{
  //initialize the variables we're linked to
  //  Input = analogRead(PIN_INPUT);
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
  leftMotorVel.SetMode(AUTOMATIC);
  leftMotorVel.SetSampleTime(1);
  leftMotorVel.SetOutputLimits(-255, 255);
  
  rightMotorVel.SetMode(AUTOMATIC);
  rightMotorVel.SetSampleTime(1);
  rightMotorVel.SetOutputLimits(-255, 255);
}

//void PID_loop()
//{
// Input = analogRead(PIN_INPUT);
//  myPID.Compute();
//  analogWrite(PIN_OUTPUT, Output);
//}
