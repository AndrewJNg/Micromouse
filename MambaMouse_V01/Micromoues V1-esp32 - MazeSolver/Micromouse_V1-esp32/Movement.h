// motor control system for TB6612FNG motor driver
// uses variables from encoder to allow better forward and backward movement
extern bool motorForward[2];

#define PWM_resolution 12
#define PWM_resolution_max_value 4095

const byte motorPin1[] =  {4, 16};
const byte motorPin2[] = {2, 17};
const byte motorPWM[] = {15, 5};

//ESP32 settings for pwm channel
const byte motorChannel[] = {0, 1};


void motor(int speedLeft, int speedRight)
{
  system();
  speedLeft = constrain(speedLeft, -PWM_resolution_max_value, PWM_resolution_max_value);
  speedRight = constrain(speedRight, -PWM_resolution_max_value, PWM_resolution_max_value);
  
  // invert motors when needed
  int Speed[2] = { -speedLeft, -speedRight};

  // for loop to run each motors individually
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    if (Speed[x] > 0)
    {
      // Forward
      digitalWrite(motorPin1[x], HIGH);
      digitalWrite(motorPin2[x], LOW);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else if (Speed[x] < 0)
    {
      // Reverse
      digitalWrite(motorPin1[x], LOW);
      digitalWrite(motorPin2[x], HIGH);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else
    {
      //Stop
      digitalWrite(motorPin1[x], HIGH);
      digitalWrite(motorPin2[x], HIGH);
      ledcWrite(motorChannel[x] , 0);
    }
  }
  enc_motor_update();
}



void Motor_setup()
{
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    // set direction pins
    pinMode(motorPin1[x], OUTPUT);
    pinMode(motorPin2[x], OUTPUT);

    //set pwm pins
    ledcSetup(motorChannel[x], 5000, PWM_resolution);
    ledcAttachPin(motorPWM[x] , motorChannel[x] );

    digitalWrite(motorPin1[x], HIGH);
    digitalWrite(motorPin2[x], HIGH);
    ledcWrite(motorChannel[x] , 0);
  }
}
