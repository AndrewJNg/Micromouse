
//                         {S1,S2,S5,S6,S3,S4}

//                         {Left_Front,Left_Angled,Left_Side,Right_Side,Right_Angled,Right_Front}
const byte IREmitPin[6] = { 25, 26, 1, 3, 27, 14 };
const byte IRRecPin[6] = { 36, 39, 32, 33, 34, 35 };
double IR_ref_value[6] = { 737, 1228, 1000, 1000, 982, 1105 }; // Calibration value


int minIR[6] = { 4095, 4095, 4095, 4095, 4095, 4095 };
int maxIR[6] = { 0, 0, 0, 0, 0, 0 };
double IRVal[6] = { 0, 0, 0, 0, 0, 0 };
double IRDistance[6] = { 0, 0, 0, 0, 0, 0 };


unsigned long IR_prevMillis = 0;

const int wall_threshold = 102; // 100 is the calibration value point, give it extra 2 to give margine for sensing


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

void read_walls()
{
   IR_update();
   SerialBT.print(" Left_Front:");
   SerialBT.print(IRDistance[0]);
   SerialBT.print(" Left_angled:");
   SerialBT.print(IRDistance[1]);
   SerialBT.print(" Right_angled:");
   SerialBT.print(IRDistance[4]);
   SerialBT.print(" Right_Front:");
   SerialBT.print(IRDistance[5]);
   SerialBT.print(" ");
   SerialBT.println();

}


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
