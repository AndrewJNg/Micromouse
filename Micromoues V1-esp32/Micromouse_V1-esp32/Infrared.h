
//                                    {S1,S2,S5,S6,S3,S4}
const byte IREmitPin[6] = {25, 26, 1, 3, 27, 14};
const byte IRRecPin[6] = {36, 39, 32, 33, 34, 35};

int IRVal[6] = {0, 0, 0, 0, 0, 0};

unsigned long IR_prevMillis = 0;

// function prototypes
void IR_setup();
void IR_update();


void IR_setup()
{
  for (int x = 0; x < sizeof(IREmitPin); x++)
  {
    pinMode(IREmitPin[x], OUTPUT);
  }
}

void IR_update()
{
  unsigned long IR_currentMillis = millis();

  // Infrared sensing at 100Hz
  if (IR_currentMillis - IR_prevMillis >= 10) {
    IR_prevMillis = IR_currentMillis;
    
    for (int x = 0; x < sizeof(IREmitPin); x++)
    {
//      int initialVal  = analogRead(IRRecPin[x]);
      digitalWrite(IREmitPin[x], HIGH);
      
      delayMicroseconds(200);
      
//      IRVal[x]  = analogRead(IRRecPin[x])- initialVal;
      IRVal[x]  = analogRead(IRRecPin[x]);
      digitalWrite(IREmitPin[x], LOW);
    }
    
  }
}


//void IR_distance()
//{
//
//
//}
