

void bluetooth_setup() {
  // Serial.begin(115200);
  SerialBT.begin("ESP32test");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}


void bluetooth_loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char value = SerialBT.read();
    // Serial.write(SerialBT.read());

    switch (value) {
      case 'L':  //Left
        commandSeq[commandStep] = 1;
        commandStep++;
        break;

      case 'I':  // Ignore
        commandSeq[commandStep] = 2;
        commandStep++;
        break;

      case 'R':  // Right
        commandSeq[commandStep] = 3;
        commandStep++;
        break;

      case 'S':  // Start
        // commandSeq[commandStep] = 4;
        commandStep = 0;
        Mode = 1;
        Start = 1;
        break;

      default:
        commandSeq[commandStep] = 0;
        break;
    }
    // for (int i=0; i < sizeof(commandSeq)/4; i++) {
    //   Serial.print(commandSeq[i]);
    //   Serial.print(" ");
    // }
    // my_list = Serial.readStringUntil('');
    Serial.println();
    // Serial.println(value);
  }
  // delay(20);
}