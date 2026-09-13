
//                         {S1,S2,S5,S6,S3,S4}
const byte IREmitPin[6] = { 25, 26, 1, 3, 27, 14 };
const byte IRRecPin[6] = { 36, 39, 32, 33, 34, 35 };

int minIR[6] = { 4095, 4095, 4095, 4095, 4095, 4095 };
int maxIR[6] = { 0, 0, 0, 0, 0, 0 };
double IRVal[6] = { 0, 0, 0, 0, 0, 0 };
double IRDistance[6] = { 0, 0, 0, 0, 0, 0 };

double IR_ref_value[6] = { 819, 1269, 1000, 1000, 1064, 1187 };


unsigned long IR_prevMillis = 0;

const int left_Wall_cal = 895;
const int right_Wall_cal = 1341;


// function prototypes
void IR_setup();
void IR_update();


void IR_setup() {
  for (int x = 0; x < sizeof(IREmitPin); x++) {
    pinMode(IREmitPin[x], OUTPUT);
  }
}

void IR_update() {
  unsigned long IR_currentMillis = millis();

  // Infrared sensing at 100Hz
  if (IR_currentMillis - IR_prevMillis >= 10) {
    IR_prevMillis = IR_currentMillis;

    for (int x = 0; x < sizeof(IREmitPin); x++) {
      // int initialVal = analogRead(IRRecPin[x]);
      delayMicroseconds(200);
      digitalWrite(IREmitPin[x], HIGH);

      delayMicroseconds(200);

      //      IRVal[x]  = analogRead(IRRecPin[x])- initialVal;
      // Serial.print(analogRead(IRRecPin[x]));

      // IRVal[x] = map(analogRead(IRRecPin[x]), minIR[x], maxIR[x], 0, 10000)/100;
      int val = analogRead(IRRecPin[x]);
      IRVal[x] = map(val, 0, 4095, 0, 10000)/100;
      IRDistance[x] = 100*log(IR_ref_value[x])/log(val);
      digitalWrite(IREmitPin[x], LOW);
      
      // Serial.print(" ");
      // Serial.print(IRVal[x]);
      // Serial.print("  ");
      // Serial.print("  ");
      // Serial.print("  ");
      
      // SerialBT.print(" ");
      // SerialBT.print(IRVal[x]);
      // SerialBT.print("  ");
    }

    // Serial.println("  ");
    // SerialBT.println("  ");
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calibration() {

    for (int i = 0; i < sizeof(IREmitPin); i++) {

      digitalWrite(IREmitPin[i], HIGH);
      delayMicroseconds(500);
      int value = analogRead(IRRecPin[i]);
      digitalWrite(IREmitPin[i], LOW);

      if (minIR[i] > value) {
        minIR[i] = value;
      } else if (maxIR[i] < value) {
        maxIR[i] = value;
      }

      // Serial.print(minIR[i]);
      // Serial.print(",");
      // Serial.print(maxIR[i]);
      // Serial.print("  ");
      // Serial.print("  ");
    }


  // Serial.println("  ");
}
