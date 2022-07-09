
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


//TaskHandle_t SecondCoreAllocation;

void setup() {
  Serial.begin(115200);
  Motor_setup();
  OLED_setup();

  IR_setup();
  Enc_setup();
  Gyro_setup();

  PS3_setup();

  PID_setup();

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  //  xTaskCreatePinnedToCore(
  //                    Core0,   /* Task function. */
  //                    "Task1",     /* name of task. */
  //                    10000,       /* Stack size of task */
  //                    NULL,        /* parameter of the task */
  //                    1,           /* priority of the task */
  //                    &SecondCoreCode,      /* Task handle to keep track of created task */
  //                    0);          /* pin task to core 0 */
}



void loop() {
  system();

  if (Start)
  {
    if (Mode == 1)
    {
      OLED_display_stats();
      float target_rpm = map(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), -255, 255, -900, 900);
      rpmMove(target_rpm, target_rpm);

    }
    else if (Mode == 2)
    {


      OLED_display_stats();
      float target_rpm = map(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), -255, 255, -300, 300);
      rpmMove(-target_rpm, target_rpm);
    }
    else if (Mode == 3)
    {
      OLED_display_stats();
      motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
    }
    else if (Mode == 4)
    {
      //       rpmMove(-20,20);
      turn(90);
      Start = false;


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
  Gyro_update();
}
//Task1code: blinks an LED every 1000 ms
//void SecondCoreCode( void * pvParameters ){
//  //Setup
//  Serial.print("Task1 running on core ");
//  Serial.println(xPortGetCoreID());
//
//
//// loop function
//  for(;;){
////    digitalWrite(2, HIGH);
////    delay(1000);
////    digitalWrite(2, LOW);
////    delay(1000);
//  }
//}
