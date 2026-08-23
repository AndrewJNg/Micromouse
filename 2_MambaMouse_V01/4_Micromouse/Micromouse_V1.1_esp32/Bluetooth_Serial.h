#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void BT_setup(){
  SerialBT.begin("Micromouse");
  SerialBT.println("Micromouse Ready");
}