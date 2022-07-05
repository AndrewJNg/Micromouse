
// function prototypes
void setup();
void loop();
void system();

#include <Wire.h>
#include "Infrared.h"
#include "AS5600.h"
#include "MPU6050.h"
#include "Movement.h"

#include "PS3.h"
#include "Speed_profile.h"
#include "Cell_movement.h"

#include "User_interface.h"



void setup() {
  //      Serial.begin(115200);
  IR_setup();
  Enc_setup();
  Gyro_setup();
  Motor_setup();

  PS3_setup();

  user_interface_setup();

}

void loop() {
  // system functions (always running)
  system();

  //fucntion
  //  align_to_front_wall();
  turn(1);
  delay(1000);

  //PS3 control
  //      motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));


}

void system()
{
  //system functions, important to keep different time sensitive functions working
  IR_update();
  Gyro_update();
  OLED_display();
}
