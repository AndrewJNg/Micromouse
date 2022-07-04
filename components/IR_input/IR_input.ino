void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(analogRead(36));
Serial.print("   ");
Serial.print(analogRead(39));
Serial.print("   ");
Serial.print(analogRead(34));
Serial.print("   ");
Serial.print(analogRead(35));
Serial.print("   ");
Serial.print(analogRead(32));
Serial.print("   ");
Serial.print(analogRead(33));

Serial.println();
}
