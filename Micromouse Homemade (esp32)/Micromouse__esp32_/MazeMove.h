

extern long L_Count;
extern long R_Count ;
extern float mm_per_pulse;
double Target = 0;

double error_old;


int  FrontLeftWall = 50;
int  FrontRightWall = 50;

void alignToWall()
{

  //  double front = 22.5;
  //  double  distance0 = (front + 10) / 0.9848;
  //  double  distance1 = (front + 10) / 0.9848;
  while (abs(analogRead(A2) - FrontLeftWall) > 10 || abs(analogRead(A1) - FrontRightWall) > 10)
  {
    //    Serial.print(analogRead(A2));
    //    Serial.print("  ");
    if (analogRead(A2) > FrontLeftWall)
    {

      motor_Speed[0] = 50;
    }
    else if (analogRead(A2) < FrontLeftWall)
    {

      motor_Speed[0] = -50;
    }
    else
    {
      motor_Speed[0] = 0;

    }
    //    Serial.print(analogRead(A1));
    //    Serial.print("  ");
    if (analogRead(A1) > FrontRightWall)
    {

      motor_Speed[1] = 50;
    }
    else if (analogRead(A1) < FrontRightWall)
    {

      motor_Speed[1] = -50;
    }
    else
    {
      motor_Speed[1] = 0;

    }
    Serial.println("  ");
    motor(motor_Speed);

  }
  motor_Speed[0] = 0;
  motor_Speed[1] = 0;
  motor(motor_Speed);
  delay(100);
  MPU6050_get_data();
  Target = MPU_Z_angle() ;
}

void EncoderTurn(int Speed, int LeftMotorMulti, int RightMotorMulti, float kp, float kd)
{

  double error =  L_Count - R_Count ;
  double corr_value =  kp * error  + kd * (error - error_old); //PD control
  error_old = error;

  motor_Speed[0] = LeftMotorMulti * (Speed - corr_value)  ;
  motor_Speed[1] = RightMotorMulti * (Speed + corr_value)  ;
  motor(motor_Speed);
}

void Forward(int Speed, long distance, float kp , float kd)
{
  long distance_Count = distance / mm_per_pulse;


  L_Count = 0;
  R_Count = 0;
  error_old = 0;
  //  Serial.println(Distance_to_Counts(100));
  while (((L_Count + R_Count) / 2) < distance_Count)
  {
    double error =  L_Count - R_Count ;
    double corr_value =  kp * error  + kd * (error - error_old); //PD control
    error_old = error;

    motor_Speed[0] = (Speed - corr_value) ;
    motor_Speed[1] = (Speed + corr_value) ;
    motor(motor_Speed);
    //    L_Count;
    //    R_Count;
    Serial.print(L_Count);
    //    Serial.print("  ");
    //    Serial.print(motor_Speed[0]);
    //
    //    Serial.print("  ");
    Serial.print("  ");
    Serial.println(R_Count);
    //    Serial.print("  ");
    //    Serial.print(motor_Speed[1]);
    //    Serial.println("  ");
  }


  motor_Speed[0] = 0;
  motor_Speed[1] = 0;
  motor(motor_Speed);

}
float precision = 1; //degree

double error_angle_old;

int lastGoalState = LOW;   // the previous reading from the input pin

unsigned long lastGoalTime = 0;
unsigned long goalDelay = 50;    // time in ms to ensurerobot stop fully in goal

void turnDegree(int Speed, int degree, float kp, float kd)
{

  MPU6050_get_data();
  //  double  currAngle = MPU_Z_angle();

  Target = Target + degree;
  L_Count = 0;
  R_Count = 0;
  error_old = 0;
  double error = 90;
  boolean repeat = 1;

  while (repeat)
  {
    error =  MPU_Z_angle() - Target ;
    double corr_value =  20 * error  + 0 * (error - error_old); //PD control
    error_angle_old = error;

    if (corr_value > Speed) corr_value = Speed;
    else if (corr_value < -Speed) corr_value = -Speed;

    motor_Speed[0] = - (corr_value)  ;
    motor_Speed[1] = (corr_value)  ;
    motor(motor_Speed);

    /*Serial.print(corr_value);
      Serial.print("  ");
      Serial.print(MPU_Z_angle());
      Serial.print("  ");
      Serial.println(Target);*/
    MPU6050_get_data();


    int GoalState = abs(error) > precision;
    if (GoalState != lastGoalState) {
      // reset the debouncing timer
      lastGoalTime = millis();
    }
    if ((millis() - lastGoalTime) > goalDelay) {
      repeat = 0;
    }
  }



  motor_Speed[0] = 0;
  motor_Speed[1] = 0;
  motor(motor_Speed);
  /*
    if (analogRead(A1) < 700 && analogRead(A2) < 700)
    {
      alignToWall();
    }*/
}


void MoveForward()
{

  Forward(100, 180, 50 , 0);
  Serial.println("Forward");

  if (analogRead(A1) < 500 && analogRead(A2) < 500)
  {
    alignToWall();
  }
//  delay(1000);
}
void TurnLeft()
{

  Serial.println("Left");
  turnDegree(100, -89, 60, 0);
  if (analogRead(A1) < 500 && analogRead(A2) < 500)
  {
    alignToWall();
  }
//  delay(1000);
}

void TurnRight()
{

  Serial.println("Right");
  turnDegree(100, 89, 60, 0);
  if (analogRead(A1) < 500 && analogRead(A2) < 500)
  {
    alignToWall();
  }
//  delay(1000);
}
