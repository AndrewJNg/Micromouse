// motor control system for TB6612FNG motor driver
// Also includes PS3 to motor control

//  motor control pin layout   [ Left Front, Right Front , Back Left , Back Right]
const byte motorPin1[] =  {6, 9};
const byte motorPin2[] = {5, 10};
//const byte motorPWM[] = {33, 15, 13, 5};
//const byte motorChannel[] = {0, 1, 2, 3};
const byte motorSTBY[] = {14};

int motor_Speed[] = {0, 0};
//const byte PWM_resolution = 8;//16;
//const int PWM_resolution_max_value = 255;//65536;


void motor(int Speed[])
{ // Translate Speed from  -255 to 255 or higher resolution to motor driver
  for (int x = 0; x < sizeof(Speed); x++)
  {
    if (Speed[x] >255) Speed[x] =255;
    else if (Speed[x] < - 255) Speed[x] =-255;
    else if (abs(Speed[x]) < 20) Speed[x] =0;
  }


  
  for (int x = 0; x < sizeof(motorSTBY); x++)
  {
    digitalWrite(motorSTBY[x], HIGH);
  }


  
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    //    if (Speed[x] > PWM_resolution_max_value) Speed[x] = PWM_resolution_max_value;
    //    else if (Speed[x] < -PWM_resolution_max_value) Speed[x] = -PWM_resolution_max_value;

    if (Speed[x] > 0)
    { // Forward
      //      digitalWrite(motorPin1[x], LOW);
      //      digitalWrite(motorPin2[x], HIGH);
      //      ledcWrite(motorChannel[x] , abs(Speed[x]));
      //      analogWrite(motorPWM[x],abs(Speed[x]));
      analogWrite(motorPin1[x], abs(Speed[x]));
      analogWrite(motorPin2[x], 0);

    }
    else if (Speed[x] < 0)
    { // Reverse
      //      digitalWrite(motorPin1[x], HIGH);
      //      digitalWrite(motorPin2[x], LOW);
      //      ledcWrite(motorChannel[x] , abs(Speed[x]));
      //      analogWrite(motorPWM[x],abs(Speed[x]));
      analogWrite(motorPin1[x], 0);
      analogWrite(motorPin2[x], abs(Speed[x]));
    }
    else
    { //Stop
      //      digitalWrite(motorPin1[x], HIGH);
      //      digitalWrite(motorPin2[x], HIGH);
      analogWrite(motorPin1[x], 0);
      analogWrite(motorPin2[x], 0);
      //      ledcWrite(motorChannel[x] , 0);
      //      analogWrite(motorPWM[x],0);
    }
  }
}


void Movement_setup()
{
  // movement setup
  for (int x = 0; x < sizeof(motorSTBY); x++)
  {
    pinMode(motorSTBY[x], OUTPUT);
    digitalWrite(motorSTBY[x], LOW);
  }
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    pinMode(motorPin1[x], OUTPUT);
    pinMode(motorPin2[x], OUTPUT);
    //    ledcSetup(motorChannel[x], 5000, PWM_resolution);
    //    ledcAttachPin(motorPWM[x] , motorChannel[x] );
  }
}
