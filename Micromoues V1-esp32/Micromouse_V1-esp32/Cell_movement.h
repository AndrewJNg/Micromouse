void align_to_front_wall( int speedTol = 100, int targetReadingLeft = 4000, int targetReadingRight = 4000)
{
  unsigned long saveMillis = millis();
  int diffL = 0;
  int diffR = 0;
  do {
    system();
    diffL = targetReadingLeft - IRVal[0] ;

    //    int maxLimit = 100;
    int maxLimit = 70;
    if ( diffL < -maxLimit)  diffL = -maxLimit;
    else if ( diffL > maxLimit)  diffL = maxLimit;
    int leftSpeed = map(diffL, -maxLimit, maxLimit, -speedTol , speedTol );

    diffR = targetReadingRight - IRVal[5] ;

    if ( diffR < -maxLimit)  diffR = -maxLimit;
    else if ( diffR > maxLimit)  diffR = maxLimit;
    int rightSpeed = map(diffR, -maxLimit, maxLimit, -speedTol , speedTol );


    if (leftSpeed < -50)  leftSpeed = -50;
    else if ( leftSpeed > 50)  leftSpeed = 50;
    if (rightSpeed < -50)  rightSpeed = -50;
    else if ( rightSpeed > 50)  rightSpeed = 50;

    motor(leftSpeed, rightSpeed);
    //    rpmMove(leftSpeed, rightSpeed);
  } while ((millis() - saveMillis) < 3000);
  motor(0, 0);
}

void move_forward_cells(int cellsNumber = 1)
{

  straight(100, 160 * cellsNumber);
  motor(0,0);
//  delay(100);
  if ( IRVal[0] >=2000 ||  IRVal[5] >= 2000)
  {
    align_to_front_wall();
  }
  
 // lane centering
//    do
//    {
//      system();
//      //    int diff = IRVal[4] - IRVal[1];
//      int diff = (leftWall - IRVal[2]) +  (IRVal[3] -rightWall);
////      int diff = (IRVal[3] -rightWall)- (leftWall - IRVal[2]);
//      if ( diff < -1500)  diff = -1500;
//      else if ( diff > 1500)  diff = 1500;
//      int speedDiff = map(diff, -1500, 1500, -70 , 70);
//      int Speed = 100;
//      motor(Speed - speedDiff, Speed + speedDiff);
//      //      Start = false;
////    } while ( (IRVal[0] < 2000 && IRVal[5] < 2000 ) && (IRVal[2] > 800 && IRVal[3] > 800));
//    } while ( (IRVal[0] < 2000 && IRVal[5] < 2000 ) && (IRVal[2] > 300 && IRVal[3] > 300));
  //  motor(0, 0);
}

// accept angle to be turned (-90, 90, 180,270)
void turn(int  turnDegree)
{
  double prevAngle;
  double targetAngle;
  prevAngle =   MPU_Z_angle();

    targetAngle = prevAngle + turnDegree;
//  targetAngle = turnDegree;
  unsigned long saveMillis = millis();

  //    prevAngle =   MPU_Z_angle();
  //
  //  turnDegree = rotation * 90;
  //  targetAngle = prevAngle + turnDegree - 5;
  while ( abs(gyroZ - targetAngle) > 3 && Start == true && ((millis()-saveMillis)<3000))
  {
    //      int speedTol = 300;
    int speedTol = 100;
    double diff = targetAngle - gyroZ ;
    if (diff < -40) diff = -40;
    else if (diff > 40) diff = 40;
    int Speed = map(diff, -40, 40, -speedTol , speedTol );
    motor(Speed, -Speed);
    //    rpmMove(Speed, -Speed);
    system();
  }

  if ( IRVal[0] >=3500 ||  IRVal[5] >= 3500)
  {
    align_to_front_wall();
  }
  //do {
  //    Input = MPU_Z_angle()-Setpoint;
  //    myPID.SetOutputLimits(-255, 255);
  //    myPID.SetTunings(Kp, Ki, Kd);
  //    myPID.Compute();
  //    int Speed = Output;
  //    if(Speed >70) Speed =70;
  //    else if(Speed <-70) Speed =-70;
  //    motor(Speed, -Speed);
  //    system();
  //    OLED_display_stats();
  //
  //  } while ((millis() - saveMillis) < 1000);

  //  while ((millis() - saveMillis) < 3000)
  //  {
  //    turnInput = MPU_Z_angle();
  //    turnSetpoint =  targetAngle;
  //    turnPID.SetTunings(turnKp, turnKi, turnKd);
  //    turnPID.Compute();
  //    int Speed = turnOutput;
  //    rpmMove(Speed, -Speed);
  //    OLED_display_stats();
  //
  //        int min = -80;
  //        Serial.print(min);
  //        Serial.print(" ");
  //        Serial.print(80);
  //        Serial.print(" ");
  //        Serial.print(turnInput);
  //        Serial.print(" ");
  //        Serial.print(turnSetpoint);
  //        Serial.println();
  //    system();
  //  }

  motor(0, 0);
}
