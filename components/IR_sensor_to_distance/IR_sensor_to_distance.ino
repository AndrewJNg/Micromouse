#include "IR_sensor.h"

//IR_sensor IR_LS(A3, 30);
IR_sensor IR_LF(17,A2, 100,3.0992e4,27.1734);
IR_sensor IR_RF(17,A1, 100,2.8006e4,44.9031);
//IR_sensor IR_RS(A1, 30);
//IR_sensor IR_RF(A0, 30);

void setup() {
  Serial.begin(115200);
}

void loop() {
//  Serial.print(IR_LS.Distance());
  Serial.print(analogRead(A2));
  Serial.print("    ");
  Serial.print(IR_LF.Distance());
  Serial.print("    ");
  Serial.print(analogRead(A1));
  Serial.print("    ");
  Serial.print(IR_RF.Distance());
  Serial.print("    ");
//  Serial.print(IR_RS.Distance());
  Serial.println("    ");
  delay(10);


}
