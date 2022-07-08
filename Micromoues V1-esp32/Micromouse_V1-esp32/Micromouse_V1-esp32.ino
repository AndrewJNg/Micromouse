
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
//double Kp = 5, Ki = 4.5, Kd = 0.03;
double Kp = 5, Ki = 5.1, Kd = 0.03;
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




void loop() {
  system();

  if (Start)
  {
    if (Mode == 1)
    {

      float target_rpm = map(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), -255, 255, -300, 300);
       rpmMove(target_rpm,target_rpm);
      //      OLED_display_stats();
      //      system();
      //OLED_display_stats();
//        Serial.println(1);

    }
    else if (Mode == 2)
    {
      

      float target_rpm = map(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), -255, 255, -300, 300);
       rpmMove(-target_rpm,target_rpm);
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

      
//      move_forward_cells();
//      align_to_front_wall();
//
//      delay(100);
//      system();
//      Setpoint = MPU_Z_angle() + 90;
//      turn(1);
//
//      align_to_front_wall();
//
//      delay(100);
//      system();
//      Setpoint = MPU_Z_angle() + 90;
//      turn(1);
//      move_forward_cells();
//      Start = false;
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
//  IR_update();
  //  Gyro_update();
}
