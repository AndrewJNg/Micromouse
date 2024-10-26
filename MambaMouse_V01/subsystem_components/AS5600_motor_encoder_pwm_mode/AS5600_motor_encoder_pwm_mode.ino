#include <Wire.h>
#include "AS5600.h"
volatile int pwm_value = 0;
volatile int prev_time = 0;
volatile int pwm_value2 = 0;
volatile int prev_time2 = 0;

byte pwm_pin = 19;
byte pwm_pin2 = 18;

void rising1() {
  attachInterrupt(digitalPinToInterrupt(pwm_pin), falling1, FALLING);
  prev_time = micros();
}

void falling1() {
  attachInterrupt(digitalPinToInterrupt(pwm_pin), rising1, RISING);
  pwm_value = micros() - prev_time;
}

void rising2() {
  attachInterrupt(digitalPinToInterrupt(pwm_pin2), falling2, FALLING);
  prev_time2 = micros();
}

void falling2() {
  attachInterrupt(digitalPinToInterrupt(pwm_pin2), rising2, RISING);
  pwm_value2 = micros() - prev_time2;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(21, 22);
  AS5600_I2C_setup();

  // when pin D2 goes high, call the rising function
  attachInterrupt(digitalPinToInterrupt(pwm_pin), rising1, RISING);
  attachInterrupt(digitalPinToInterrupt(pwm_pin2), rising2, RISING);

  Serial.println("Ready");


}
void loop() {
 
//  value =  AS5600_I2C_update();
//  Serial.print(value);
//  Serial.print("\t");
  //32 -1056
  Serial.print("\t");
  Serial.print(pwm_value);
  Serial.print("\t");
  Serial.print(map(pwm_value, 31, 1077, 0, 3599));
  Serial.print("\t");
  Serial.print(pwm_value2);
  Serial.print("\t");
  Serial.println(map(pwm_value2, 32, 1056, 0, 359));
}
