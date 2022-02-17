long x=0;
long t;
void setup() {
  Serial.begin(57600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(6, OUTPUT);
attachInterrupt(digitalPinToInterrupt(2), Set_1, CHANGE);
attachInterrupt(digitalPinToInterrupt(3), Set_2, CHANGE);
}
void loop() {
//  noInterrupts();
  // critical, time-sensitive code here
//  interrupts();
  //Serial.print(digitalRead(2));
  if (x<4050){
    analogWrite(6,150);
    t=millis();
  }
  else{
    digitalWrite(6,LOW);
  }
  Serial.print(x);
  Serial.print("     ");
  Serial.print(t);
  Serial.print("     ");
  Serial.println(millis());
  
}
void Set_1() {
  x++;
}
void Set_2() {
  x++;
}
