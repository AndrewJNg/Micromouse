void align_to_front_wall( int speedTol = 200, int targetReadingLeft = 4000, int targetReadingRight = 4000)
{
  unsigned long saveMillis = millis();
  saveMillis = millis();
  int diffL = 0;
  int diffR = 0;
  //  do
  //  {
  do {
    system();
    diffL = targetReadingLeft - IRVal[0] ;

    int maxLimit = 300;
    if ( diffL < -maxLimit)  diffL = -maxLimit;
    else if ( diffL > maxLimit)  diffL = maxLimit;
    int leftSpeed = map(diffL, -maxLimit, maxLimit, -speedTol , speedTol );

    diffR = targetReadingRight - IRVal[5] ;

    if ( diffR < -maxLimit)  diffR = -maxLimit;
    else if ( diffR > maxLimit)  diffR = maxLimit;
    int rightSpeed = map(diffR, -maxLimit, maxLimit, -speedTol , speedTol );


    if (leftSpeed < -70)  leftSpeed = -70;
    else if ( leftSpeed > 70)  leftSpeed = 70;
    if (rightSpeed < -70)  rightSpeed = -70;
    else if ( rightSpeed > 70)  rightSpeed = 70;

    motor(leftSpeed, rightSpeed);
  } while ((millis() - saveMillis) < 1000);
  motor(0,0);
  //  } while (abs(diffR + diffL) > 500);
}

void move_forward_cells(int cellsNumber = 1)
{

  do
  {
    system();
    int diff = IRVal[4] - IRVal[1];
    if ( diff < -500)  diff = -500;
    else if ( diff > 500)  diff = 500;
    int speedDiff = map(diff, -500, 500, -60 , 60);
    int Speed = 100;
    motor(Speed - speedDiff, Speed + speedDiff);
    //      Start = false;
  } while ( (IRVal[0] < 2000 && IRVal[5] < 2000 ) && (IRVal[2] > 800 && IRVal[3] > 800));
  motor(0,0);
}


void turn(int rotation)
{
  //  rotation = -1(turn Left) /1(turn Right) / 2 (turn 180 )
  double prevAngle;
  double targetAngle;
  int turnDegree;

//  prevAngle =   MPU_Z_angle();
//
//  turnDegree = rotation * 90;
//  targetAngle = prevAngle + turnDegree - 5;


  unsigned long saveMillis = millis();
  //  while ( abs(gyroZ - targetAngle) > 3 && Start == true)
  //  {
  //    int speedTol = 300;
  //    double diff = targetAngle - gyroZ ;
  //    if (diff < -90) diff = -90;
  //    else if (diff > 90) diff = 90;
  //    int Speed = map(diff, -90, 90, -speedTol , speedTol );
  //    motor(Speed, -Speed);
  //    system();
  //  }
//  Setpoint = prevAngle + turnDegree;

  do {
    Input = MPU_Z_angle()-Setpoint;
    myPID.SetOutputLimits(-255, 255);
    myPID.SetTunings(Kp, Ki, Kd);
    myPID.Compute();
    int Speed = Output;
    if(Speed >70) Speed =70;
    else if(Speed <-70) Speed =-70;
    motor(Speed, -Speed);
    system();
    OLED_display_stats();

  } while ((millis() - saveMillis) < 1000);
  motor(0,0);

//  motor(0, 0);
//  delay(2000);
}
