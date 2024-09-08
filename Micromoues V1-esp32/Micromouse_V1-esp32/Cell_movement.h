
int cell_distance = 180; //180mm from center to center of the cells


void align_to_front_wall( int speedTol = 200, int targetReadingLeft = 100, int targetReadingRight = 100)
{
  unsigned long saveMillis = millis();
  int diffL = 0;
  int diffR = 0;
  do {
    system();
    diffL = targetReadingLeft - IRVal[0] ;
    diffR = targetReadingRight - IRVal[5] ;

    //    int maxLimit = 100;
    int maxLimit = 100;
    if ( diffL < -maxLimit)  diffL = -maxLimit;
    else if ( diffL > maxLimit)  diffL = maxLimit;

    if ( diffR < -maxLimit)  diffR = -maxLimit;
    else if ( diffR > maxLimit)  diffR = maxLimit;



    int leftSpeed = map(diffL, -maxLimit, maxLimit, -speedTol , speedTol );
    int rightSpeed = map(diffR, -maxLimit, maxLimit, -speedTol , speedTol );


    if (leftSpeed < -80)  leftSpeed = -80;
    else if ( leftSpeed > 80)  leftSpeed = 80;
    if (rightSpeed < -80)  rightSpeed = -80;
    else if ( rightSpeed > 80)  rightSpeed = 80;

    motor(leftSpeed, rightSpeed);
    //    rpmMove(leftSpeed, rightSpeed);
  } while ((millis() - saveMillis) < 3000);
  motor(0, 0);
}


void straight(int Speed, long targetDistance) {
  double initLeftDist = encDistance(0);
  double initRightDist = encDistance(1);
  double currLeftDist = 0;
  double currRightDist = 0;

  //  Serial.print(initLeftDist);
  //  Serial.print("  ");
  //  Serial.print(initRightDist );
  //  Serial.print("  ");
  //  Serial.print(currLeftDist);
  //  Serial.print("  ");
  //  Serial.print(currRightDist);
  //  error_old = 0;

  currLeftDist = encDistance(0) - initLeftDist;
  currRightDist = encDistance(1) - initRightDist;


  while ((((currLeftDist + currRightDist) / 2) < targetDistance) && Start == true && (IRVal[0] < 3500 && IRVal[5] < 3500)) {
    currLeftDist = encDistance(0) - initLeftDist;
    currRightDist = encDistance(1) - initRightDist;


    // both walls are present
    if (IRVal[2] >= 1500 && IRVal[3] >= 1500) {
      system();
      //    int diff = IRVal[4] - IRVal[1];
      int diff = (leftWall - IRVal[2]) + (IRVal[3] - rightWall);
      //      int diff = (IRVal[3] -rightWall)- (leftWall - IRVal[2]);
      if (diff < -1500) diff = -1500;
      else if (diff > 1500) diff = 1500;
      int speedDiff = map(diff, -1500, 1500, -70, 70);
      int Speed = 100;
      motor(Speed - speedDiff, Speed + speedDiff);
    } 
    
    // if left wall is present, right wall is empty
    else if (IRVal[2] >= 1500 && IRVal[3] < 1500) {
      system();
      //    int diff = IRVal[4] - IRVal[1];
      int diff = (leftWall - IRVal[2]);
      //      int diff = (leftWall - IRVal[2]) +  (IRVal[3] - rightWall);
      //      int diff = (IRVal[3] -rightWall)- (leftWall - IRVal[2]);
      if (diff < -1500) diff = -1500;
      else if (diff > 1500) diff = 1500;
      int speedDiff = map(diff, -1500, 1500, -70, 70);
      int Speed = 100;
      motor(Speed - speedDiff, Speed + speedDiff);
    } 
    
    
    
    
    // if left wall is empty, right wall is present
    else if (IRVal[2] < 1500 && IRVal[3] >= 1500) {
      system();
      //    int diff = IRVal[4] - IRVal[1];
      int diff = (IRVal[3] - rightWall);
      //      int diff = (leftWall - IRVal[2]) +  (IRVal[3] - rightWall);
      //      int diff = (IRVal[3] -rightWall)- (leftWall - IRVal[2]);
      if (diff < -1500) diff = -1500;
      else if (diff > 1500) diff = 1500;
      int speedDiff = map(diff, -1500, 1500, -70, 70);
      int Speed = 100;
      motor(Speed - speedDiff, Speed + speedDiff);
    } 
    
    
    
    // both walls are empty
    else {
      //    double error =  currLeftDist - currRightDist ;
      //    double corr_value =  kp * error  + kd * (error - error_old); //PD control
      //    error_old = error;

      straightInput = currRightDist - currLeftDist;
      straightSetpoint = 0;
      straightPID.SetTunings(straightKp, straightKi, straightKd);
      straightPID.Compute();
      int corr_value = straightOutput;
      //    rpmMove(Speed, -Speed);

      //    rpmMove(Speed - corr_value, Speed + corr_value);
      motor(Speed - corr_value, Speed + corr_value);
      system();
    }

  }
}



void move_forward_cells(int cellsNumber = 1)
{
  straight(100, 160 * cellsNumber);
  motor(0,0);
//  delay(100);
  if ( IRVal[0] >=50 ||  IRVal[5] >= 50)
  {
    align_to_front_wall();
  }
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
    if (diff < -20) diff = -20;
    else if (diff > 20) diff = 20;
    int Speed = map(diff, -20, 20, -speedTol , speedTol );
    motor(Speed, -Speed);
    //    rpmMove(Speed, -Speed);
    system();
  }

  // Aligning to front wall
  if ( IRVal[0] >=50 ||  IRVal[5] >= 50)
  {
    align_to_front_wall();
  }
  
  motor(0, 0);
  
}


