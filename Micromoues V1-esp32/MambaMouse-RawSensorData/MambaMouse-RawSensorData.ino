#include <Wire.h>
#include "AS5600.h"
#include "MPU6050.h"
#include "User_interface.h"
#include "Movement.h"

void setup() {
  // put your setup code here, to run once:

//  Serial.begin(115200);
  Movement_setup();
  AS5600_I2C_setup_1();
  AS5600_I2C_setup_2();
  MPU6050_setup();
  User_interface_setup();
  OLED_display();
//  Serial.println("Ready");
pinMode(27,OUTPUT); //S3
pinMode(14,OUTPUT); //S4
pinMode(3,OUTPUT); //S6

pinMode(25,OUTPUT); //S1
pinMode(26,OUTPUT); //S2
pinMode(1,OUTPUT); //S5

}

void loop() {

digitalWrite(25,HIGH);
delay(5);
IRFrontL = analogRead(36); //S1
digitalWrite(25,LOW);

digitalWrite(26,HIGH);
delay(5);
IR45L = analogRead(39);  //S2
digitalWrite(26,LOW);

digitalWrite(1,HIGH);
delay(5);
IRSideL = analogRead(32); //S5
digitalWrite(1,LOW);


digitalWrite(27,HIGH);
delay(5);
IR45R = analogRead(34); //S3
digitalWrite(27,LOW);

digitalWrite(14,HIGH);
delay(5);
IRFrontR = analogRead(35);  //S4
digitalWrite(14,LOW);

digitalWrite(3,HIGH);
delay(5);
IRSideR = analogRead(33); //S6
digitalWrite(3,LOW);


  motor_Speed[0] = 0;
  motor_Speed[1] = 0;
motor(motor_Speed);
//  Serial.print(AS5600_I2C_update_1());
//  Serial.print("\t");
//  Serial.print(AS5600_I2C_update_2());
//  Serial.print("\t");
  MPU6050_get_data();
  OLED_display();
//  Serial.println();
}
