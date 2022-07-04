#include <Wire.h>
#include "Infrared.h"
#include "AS5600.h"
#include "MPU6050.h"
#include "Movement.h"

#include "PS3.h"

#include "User_interface.h"

void setup() {

  //  Serial.begin(115200);
  IR_setup();
  encoder_setup();
  MPU6050_setup();
  movement_setup();
  
  PS3_setup();
  
  user_interface_setup();

}

void loop() {
  update_IR_val();
  MPU6050_get_data();
  OLED_display();
  motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
//  motor(255,255);

}
