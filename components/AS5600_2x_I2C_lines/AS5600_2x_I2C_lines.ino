#include <Wire.h>
#include "AS5600.h"

void setup() {
  // put your setup code here, to run once:

  Wire.begin(SDA_1, SCL_1, 100000);
  Serial.begin(115200);
  AS5600_I2C_setup_1();
  AS5600_I2C_setup_2();

  Serial.println("Ready");
}
void loop() {

  Serial.print(AS5600_I2C_update_1());
  Serial.print("\t");
  // Serial.print(analogRead(34));
  Serial.print(AS5600_I2C_update_2());
  Serial.println();
}
