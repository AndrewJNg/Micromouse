
// function prototypes
void setup();
void loop();
void system();

double startPoint = 0;
double endPoint = 0;
int Mode = 1;// set mode 1 as default
boolean Start = false;
unsigned long StartTimer = 0;

//double Kp = 1.8, Ki = 1.8, Kd = 0.12;
double Kp = 5, Ki = 4.5, Kd = 0.03;
double Setpoint, Input, Output;
double rpmSetLeft, InputRpmLeft, OutputLeftMotor;
double rpmSetRight, InputRpmRight, OutputRightMotor;

#include <Wire.h>
#include "Infrared.h"
#include "AS5600.h"
#include "MPU6050.h"
#include "Movement.h"
#include "PID.h"

#include "PS3.h"
#include "Speed_profile.h"

#include "User_interface.h"
#include "OLED.h"

#include "Cell_movement.h"



void setup() {
  Serial.begin(115200);
  Motor_setup();
  OLED_setup();

  IR_setup();
  Enc_setup();
  //  Gyro_setup();

  PS3_setup();

  PID_setup();

}


int prevCountLeft = 0;
int prevCountRight = 0;
unsigned long prevMicro = 0;
unsigned long EncprevMicro = 0;
float avr_7_point[50] = {0, 0, 0, 0, 0, 0, 0};
float target_rpm = 300;

float v1Filt = 0;
float v1Prev = 0;
float v2Filt = 0;
float v2Prev = 0;

void loop() {
  system();

  if (Start)
  {
    if (Mode == 1)
    {

      //      OLED_display_stats();
      //      system();
      int interval = 1000;
      unsigned long timeDIff = micros() - EncprevMicro;
      target_rpm = map(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), -255, 255, -600, 600);


      if (timeDIff >= interval) {

        //              Serial.print(((((double) currAngle[0]-prevCount)*interval) / 1000000)/4096);
        float rpmLeft = (float)((currAngle[0] - prevCountLeft) * (1.0 / ((float)timeDIff * 1e-6)) * 60) / 4096;
        float rpmRight = (float)((currAngle[1] - prevCountRight ) * (1.0 / ((float)timeDIff * 1e-6)) * 60) / 4096;
        prevCountLeft = currAngle[0];
        prevCountRight = currAngle[1];
        EncprevMicro = micros();
        //        motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));

        float v1 = rpmLeft;

        //        v1Filt =0.99937188*v1Filt + 0.00031406*v1+0.00031406*v1Prev;  //0.1 hz
        //        v1Filt =0.99686333*v1Filt + 0.00156833*v1+0.00156833*v1Prev;  //0.5 hz
        v1Filt = 0.98751209 * v1Filt + 0.00624395 * v1 + 0.00624395 * v1Prev; //2 hz
        //        v1Filt = 0.854*v1Filt + 0.0728*v1+0.0828*v1Prev;            //5 hz
        v1Prev = v1;

        float v2 = rpmRight;
        v2Filt = 0.98751209 * v2Filt + 0.00624395 * v2 + 0.00624395 * v2Prev;;
        v2Prev = v2;


        //        Input = v1Filt- (target_rpm-100)  ;
        //        myPID.SetSampleTime(1);
        //        myPID.SetOutputLimits(-255, 255);
        //        myPID.SetTunings(Kp, Ki, Kd);
        //        myPID.Compute();
        //        int Speed = Output;
        //        motor(Speed,0);

        //        InputRpmLeft = v1Filt-100;
        //        rpmSetLeft = target_rpm;
        InputRpmLeft = v1Filt;
        rpmSetLeft = target_rpm;
        leftMotorVel.SetTunings(Kp, Ki, Kd);
        //        leftMotorVel.SetSampleTime(1);
        //        leftMotorVel.SetOutputLimits(-255, 255);
        leftMotorVel.Compute();
        int SpeedLeft = OutputLeftMotor;

        InputRpmRight = v2Filt;
        rpmSetRight = target_rpm;
        rightMotorVel.SetTunings(Kp, Ki, Kd);
        rightMotorVel.Compute();
        int SpeedRight = OutputRightMotor;


        //        motor(SpeedLeft, 0);
        motor(SpeedLeft, SpeedRight);
        //        Serial.print(v1, 0);
        Serial.print("  ");
        Serial.print(v1Filt, 0);
        Serial.print("  ");
        Serial.print(v2Filt, 0);
        Serial.print("  ");
        Serial.print(target_rpm, 0);
        Serial.print("  ");
        Serial.print(0, 0);
        Serial.print("  ");
        Serial.print(900, 0);
        Serial.println();

      }
      //OLED_display_stats();

      //  if(currAngle[0]!=prevCount)
      //      {
      //
      //      Serial.println(currAngle[0]-prevCount);
      ////      Serial.print("  ");
      ////      Serial.println(micros()-prevMicro);
      //
      //      prevCount = currAngle[0];
      //      prevMicro = micros();
      //      }
      ////      Setpoint = 90;
      ////      turn(1);
      ////      Setpoint = 0;
      ////      turn(-1);
    }
    else if (Mode == 2)
    {
      //      OLED_display_stats();
      //      system();
      //      motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
      //
      //      if(currAngle[1]!=prevCount)
      //      {
      //
      //      Serial.print(currAngle[1]-prevCount);
      //      Serial.print("  ");
      //      Serial.println(micros()-prevMicro);
      //
      //      prevCount = currAngle[1];
      //      prevMicro = micros();
      //      }
      move_forward_cells();
      align_to_front_wall();

      delay(100);
      system();
      Setpoint = MPU_Z_angle() + 90;
      turn(1);

      align_to_front_wall();

      delay(100);
      system();
      Setpoint = MPU_Z_angle() + 90;
      turn(1);
      move_forward_cells();
      Start = false;
    }
    else if (Mode == 3)
    {
      OLED_display_stats();
      motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
    }
    else if (Mode == 4)
    {

    }
  }
  else
  {
    motor(0, 0);
    OLED_menu_display();
    //    enc_menu_update();
    //    IR_left_menu.count(left_IR_button(), &Mode, -1);
    //    IR_right_menu.count(right_IR_button(), &Mode, 1);
    if        (Mode > 4)  Mode = 1;
    else if (Mode < 1)  Mode = 4;

  }
}

void system()
{
  //system functions, important to keep different time sensitive functions working
  IR_update();
  //  Gyro_update();
}
