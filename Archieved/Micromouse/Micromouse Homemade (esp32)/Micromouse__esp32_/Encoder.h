
const byte interruptPinLeft = 1;
const byte interruptPinRight = 0;
long L_Count = 0;
long R_Count = 0;

int CPR = 1000;
float Diameter = 35; // in mm

float mm_per_pulse = 0.105;

unsigned long LeftMillis = 0;
unsigned long LeftTimeDiff = 0;
unsigned long RightMillis = 0;
unsigned long RightTimeDiff = 0;

void LeftCounter()
{

  L_Count  ++;
  LeftTimeDiff = micros() -  LeftMillis;
  LeftMillis = micros();

}

void RightCounter()
{
  R_Count ++;
  RightTimeDiff = micros() -  RightMillis;
  RightMillis = micros();
}

void Encoder_setup() {
  pinMode(interruptPinLeft, INPUT_PULLUP);
  pinMode(interruptPinRight, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinLeft), LeftCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPinRight), RightCounter, FALLING);
}

double enc_vel(int select)
{
  double Circumference = (PI * Diameter )  / CPR;
  double Speed = 0;
  if (select == 0)
  {
    Speed = (Circumference * 1000000) / LeftTimeDiff  ; //cm per second
  }
  else
  {
    Speed = (Circumference * 1000000) / RightTimeDiff ; //cm per second
  }
  return Speed ;
}

double Counts_to_Distance(int Counts)
{
  double Circumference = (PI * Diameter ) * Counts / CPR;
  return Circumference;
}


double Distance_to_Counts(int Distance)
{
  double Counts =  (Distance * CPR) / (PI * Diameter ) ;
  return Counts;

}

double LeftSpeed()
{

}

double RightSpeed()
{

}
