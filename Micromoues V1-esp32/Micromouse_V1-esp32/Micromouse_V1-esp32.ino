#include <Wire.h>
#include "Infrared.h"
#include "AS5600.h"
#include "MPU6050.h"
#include "Movement.h"

#include "PS3.h"

#include "User_interface.h"

void setup() {

  //    Serial.begin(115200);
  IR_setup();
  encoder_setup();
  MPU6050_setup();
  movement_setup();

  PS3_setup();

  user_interface_setup();

}

void loop() {
  update_IR();
  gyro_get_data();
  OLED_display();
//  int leftSpeed = 0;
//  int rightSpeed = 0;
//  if (IRVal[0] < 1800)
//  {
//    leftSpeed = 50;
//  }
//  else if (IRVal[0] > 2200)
//  {
//    leftSpeed = -50;
//  }
//  else
//  {
//    leftSpeed = 0;
//
//  }
//
//
//  if (IRVal[5] < 1800)
//  {
//    rightSpeed = 50;
//  }
//  else if (IRVal[5] > 2200)
//  {
//    rightSpeed = -50;
//  }
//  else
//  {
//rightSpeed =0;
//  }
    motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
//  motor(leftSpeed, rightSpeed);

}
