/********************************************************
   PID Basic Example
   Reading analog input 0 to control analog PWM output 3
 ********************************************************/
//https://github.com/br3ttb/Arduino-PID-Library/
#include <PID_v1.h>

//#define PIN_INPUT 0
//#define PIN_OUTPUT 3

//Define Variables we'll be connecting to

//Specify the links and initial tuning parameters
PID leftMotorVel(&InputRpmLeft, &OutputLeftMotor, &rpmSetLeft, Kp, Ki, Kd, DIRECT);
PID rightMotorVel(&InputRpmRight, &OutputRightMotor, &rpmSetRight, Kp, Ki, Kd, DIRECT);

PID turnPID(&turnInput, &turnOutput, &turnSetpoint, turnKp, turnKi, turnKd, DIRECT);
PID straightPID(&straightInput, &straightOutput, &straightSetpoint, straightKp, straightKi, straightKd, DIRECT);

PID linePID(&lineInput, &lineOutput, &lineSetpoint, lineKp, lineKi, lineKd, DIRECT);
// PID straightPID(&straightInput, &straightOutput, &straightSetpoint, straightKp, straightKi, straightKd, DIRECT);

void PID_setup()
{
  //initialize the variables we're linked to
  //  Input = analogRead(PIN_INPUT);
  //  Setpoint = 100;

  leftMotorVel.SetMode(AUTOMATIC);
  leftMotorVel.SetSampleTime(10);
  leftMotorVel.SetOutputLimits(-255, 255);

  rightMotorVel.SetMode(AUTOMATIC);
  rightMotorVel.SetSampleTime(10);
  rightMotorVel.SetOutputLimits(-255, 255);

  turnPID.SetMode(AUTOMATIC);
  turnPID.SetSampleTime(10);
  turnPID.SetOutputLimits(-100, 100);  // turn speed

  straightPID.SetMode(AUTOMATIC);
  straightPID.SetSampleTime(10);
  straightPID.SetOutputLimits(-255, 255);  // turn speed
  
  linePID.SetMode(AUTOMATIC);
  linePID.SetSampleTime(10);
  linePID.SetOutputLimits(-255, 255);  // line following PID
}
