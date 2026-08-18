#include "IR_sensor.h"
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define IR_LF_PIN  36
#define IR_RF_PIN  35


//IR_sensor IR_LS(A3, 30);
IR_sensor IR_LF(25,IR_LF_PIN, 100,150.188,39.49);
IR_sensor IR_RF(14,IR_RF_PIN, 100,150.188,39.49);
//IR_sensor IR_RS(A1, 30);
//IR_sensor IR_RF(A0, 30);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Micromouse");
  SerialBT.println("Micromouse Ready");
}

void loop() {
//  Serial.print(IR_LS.Distance());

  double value = IR_LF.Distance();
  SerialBT.print(value);
  SerialBT.print("\t");
  Serial.print(value);
  Serial.print("\t");

  value = IR_RF.Distance();

  SerialBT.print(value);
  SerialBT.print("\t");
  Serial.print(value);
  Serial.print("\t");
//  Serial.print(IR_RS.Distance());
  SerialBT.println("    ");
  Serial.println("    ");
  delay(10);


}
