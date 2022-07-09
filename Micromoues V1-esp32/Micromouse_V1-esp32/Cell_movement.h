void align_to_front_wall( int speedTol = 200, int targetReadingLeft = 4000, int targetReadingRight = 4000)
{
  unsigned long saveMillis = millis();
  saveMillis = millis();
  int diffL = 0;
  int diffR = 0;
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
  motor(0, 0);
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
  motor(0, 0);
}

// accept angle to be turned (-90, 90, 180,270)
void turn(int  turnDegree)
{
  double prevAngle;
  double targetAngle;
  prevAngle =   MPU_Z_angle();

  targetAngle = prevAngle + turnDegree;

  unsigned long saveMillis = millis();
  //    while ((millis() - saveMillis) < 3000)
  //    {
  //      int speedTol = 150;
  //      double diff = targetAngle - gyroZ ;
  //      if (diff < -60) diff = -60;
  //      else if (diff > 60) diff = 60;
  //      int Speed = map(diff, -60,60, -speedTol , speedTol );
  ////      motor();
  //    rpmMove(Speed, -Speed);
  //      system();
  //    }


  //PID turnPID(&turnInput, &turnOutput, &turnSetpoint, turnKp, turnKi, turnKd, DIRECT);

  while ((millis() - saveMillis) < 3000)
  {
    turnInput = MPU_Z_angle();
    turnSetpoint =  targetAngle;
    turnPID.SetTunings(turnKp, turnKi, turnKd);
    turnPID.Compute();
    int Speed = turnOutput;
    rpmMove(Speed, -Speed);
    OLED_display_stats();
    system();
  }

  motor(0, 0);
}
