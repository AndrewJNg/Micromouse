
// function prototypes
void setup();
void loop();
void system();

double startPoint = 0;
double endPoint = 0;
unsigned int Mode = 1;// set mode 1 as default
boolean Start = false;
unsigned long StartTimer = 0;

#include <Wire.h>
#include "Infrared.h"
#include "AS5600.h"
#include "MPU6050.h"
#include "Movement.h"

#include "PS3.h"
#include "Speed_profile.h"
#include "Cell_movement.h"

#include "User_interface.h"
#include "OLED.h"



void setup() {
  Serial.begin(115200);
  IR_setup();
  Enc_setup();
  Gyro_setup();
  Motor_setup();

  PS3_setup();

  OLED_setup();

}
void loop() {
  system();
  
  if (Start)
  {
    if (Mode == 1)
    {
      OLED_display_stats();
      int leftInitDistance = encDistance(0);
      int rightInitDistance = encDistance(1);
      Serial.print(leftInitDistance);
      Serial.print("  ");
      Serial.print(rightInitDistance);
      Serial.print("  ");
      int leftSpeed = 100;
      int rightSpeed = 100;
      int  diff = encDistance(0) - encDistance(1);

      if ( diff < -100)  diff = -100;
      else if ( diff > 100)  diff = 100;
      int diffSpeed = map(diff, -100, 100, -20 , 20 );


      motor(leftSpeed - diffSpeed, rightSpeed + diffSpeed);
      Serial.print(diff);
      Serial.print("  ");
      Serial.print(diffSpeed);
      Serial.print("  ");
      //
      //      startPoint = ((encDistance(0) - leftInitDistance) + (encDistance(1) - rightInitDistance)) / 2;
      //      while (((((encDistance(0) - leftInitDistance) + (encDistance(1) - rightInitDistance)) / 2) - startPoint) < 180)
      //      {
      //        system();
      //        //        move_forward_cells();
      //        motor(100, 100);
      //        OLED_display_stats();
      //      }
      //      motor(0, 0);
      //      endPoint = ((encDistance(0) - leftInitDistance) + (encDistance(1) - rightInitDistance)) / 2;
      //      OLED_display_stats();
      //      Serial.print(encDistance(0) - leftInitDistance);
      //      Serial.print("  ");
      //
      //      Serial.print(encDistance(1) - rightInitDistance);
      //      Serial.println("  ");
      //
      //      delay(5000);

      Serial.println("  ");
      //      Start = false;
      //      motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
    }
    else if (Mode == 2)
    {
      move_forward_cells();
      align_to_front_wall();
      turn(1);

      align_to_front_wall();
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
    OLED_menu_display();
    //    enc_menu_update();
    //    count_minus();
    //    count_plus();
    motor(0, 0);
    if (Mode > 4)
    {
      Mode = 1;
    }
    else if (Mode < 1)
    {
      Mode = 4;
    }
  }
}

void system()
{
  //system functions, important to keep different time sensitive functions working
  IR_update();
  Gyro_update();
}
