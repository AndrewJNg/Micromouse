
//                                    {S1,S2,S5,S6,S3,S4}
// const byte IREmitPin[6] = { };
// const byte IRRecPin[6] = { 36, 39, 32, 33, 34, 35 };
// int IRVal[6] = { 0, 0, 0, 0, 0,0};

const byte LED_Pin[5] = { 25, 26, 1, 27, 14 };
const byte IRRecPin[5] = { 36, 39, 32, 34, 35 };
int IRVal[5] = { 0, 0, 0, 0, 0 };

unsigned long IR_prevMillis = 0;

unsigned int minIR[sizeof(IRRecPin)];
unsigned int midIR[sizeof(IRRecPin)];
unsigned int maxIR[sizeof(IRRecPin)];
unsigned int get_state[sizeof(IRRecPin)];

boolean whiteLine = false;  // set to follow a white line if true
// function prototypes
void IR_setup();
void IR_update();


void IR_setup() {
  // LED pinMode setup
  for (int ledCount = 0; ledCount < (sizeof(LED_Pin)); ledCount++)
    pinMode(LED_Pin[ledCount], OUTPUT);
}

void IR_calibrate() {
}

void IR_update() {
  unsigned long IR_currentMillis = millis();

  // Infrared sensing at 100Hz
  if (IR_currentMillis - IR_prevMillis >= 10) {
    IR_prevMillis = IR_currentMillis;
    
    for (int ledCount = 0; ledCount < (sizeof(IRRecPin)); ledCount++) {
      // Infrared sensing
      IRVal[ledCount] = analogRead(IRRecPin[ledCount]);
      int valueIR = analogRead(IRRecPin[ledCount]);

      // Apply value to binary output
      // if (valueIR > midIR[ledCount]) get_state[ledCount] = 1;
      if (valueIR > 1000) get_state[ledCount] = 1;
      else get_state[ledCount] = 0;

      // Invert if the line is white
      if (!whiteLine) get_state[ledCount] = 1 - get_state[ledCount];

      // Show binary output on front LEDs
      digitalWrite(LED_Pin[ledCount], get_state[ledCount]);
    }
  }
}
