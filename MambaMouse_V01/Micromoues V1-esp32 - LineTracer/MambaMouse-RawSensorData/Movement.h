// motor control system for TB6612FNG motor driver
// Also includes PS3 to motor control


//  motor control pin layout   [ Left Front, Right Front , Back Left , Back Right]
//const byte motorPin1[] =  {17, 4};
//const byte motorPWM[] = {5,  16};

const byte motorPin1[] =  {4,16};
const byte motorPin2[] = {2,17};

const byte motorPWM[] = {15,5};

const byte motorChannel[] = {0, 1};
//const byte motorSTBY[] = {27};

int motor_Speed[] = {0, 0};
const byte PWM_resolution = 8;//16;
const int PWM_resolution_max_value = 255;//65536;


void motor(int Speed[])
{
  // invert back motors of the system
  Speed[0] = Speed[0];
  Speed[1] = Speed[1];

 // for loop to run each motors individually
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
  
    if (Speed[x] > 0)
    { // Forward
      digitalWrite(motorPin1[x], HIGH);
      digitalWrite(motorPin2[x], LOW);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else if (Speed[x] < 0)
    { // Reverse
      digitalWrite(motorPin1[x], LOW);
      digitalWrite(motorPin2[x], HIGH);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else
    { //Stop
      digitalWrite(motorPin1[x], HIGH);
      digitalWrite(motorPin2[x], HIGH);
      ledcWrite(motorChannel[x] , 0);
    }
  }
  
}



void Movement_setup()
{
  // movement setup

  // activate Standby pin 
//  for (int x = 0; x < sizeof(motorSTBY); x++)
//  {
//    pinMode(motorSTBY[x], OUTPUT);
//  }

// set motor pins as output
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    pinMode(motorPin1[x], OUTPUT);
    pinMode(motorPin2[x], OUTPUT);
    ledcSetup(motorChannel[x], 5000, PWM_resolution);
    ledcAttachPin(motorPWM[x] , motorChannel[x] );
  }
}
