void align_to_front_wall( int speedTol = 200, int targetReadingLeft = 3200, int targetReadingRight = 3200)
{
  int diffL = targetReadingLeft - IRVal[0] ;
  int leftSpeed = map(diffL, -2000, 2000, -speedTol , speedTol );

  int diffR = targetReadingRight - IRVal[5] ;
  int rightSpeed = map(diffR, -2000, 2000, -speedTol , speedTol );
  motor(leftSpeed, rightSpeed);
}

void move_forward_cells(int cellsNumber = 1)
{

}


void turn(int rotation)
{
  //  rotation = -1(turn Left) /1(turn Right) / 2 (turn 180 )
  double prevAngle;
  double targetAngle;
  int turnDegree;

  prevAngle =   gyroZ;

  turnDegree = rotation * 90;
  targetAngle = prevAngle + turnDegree;
  while ( abs(gyroZ - targetAngle) > 1)
  {
    int speedTol = 255;
    double diff = targetAngle - gyroZ ;
    int Speed = map(diff, -90, 90, -speedTol , speedTol );
    motor(Speed, -Speed);

    system();
  }


}
