int LED[] = {14, 27, 26, 25, 1, 3} ;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 6; i++)
  {
    pinMode(LED[i], OUTPUT);

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(LED[i], HIGH);
    delay(500);
    digitalWrite(LED[i], LOW);

  }
}
