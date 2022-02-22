
#include "IR_sensor.h"
#include "Movement.h"
#include "MPU6050.h"
#include "MazeMove.h"
#include "Encoder.h"
#include "FloodFill.h"

//IR_sensor IR_LS(A3, 30);

IR_sensor IR_LS(17, A3, 100, 3.0992e4, 27.1734);
IR_sensor IR_LF(17, A2, 100, 3.0992e4, 27.1734);
IR_sensor IR_RF(17, A1, 100, 2.8006e4, 44.9031);
IR_sensor IR_RS(17, A0, 100, 2.8006e4, 44.9031);

//IR_sensor IR_RS(A1, 30);

void setup() {

  Serial.begin(115200);
  Movement_setup();
  delay(2000);
  MPU6050_setup();
  Encoder_setup();
  FloodFill_setup();

  //  setWall(0, 1, 'n');
  //  setWall(1, 1, 'n');
  //  setWall(2, 1, 'n');
  //  setWall(3, 1, 'n');
  //
  //  setWall(0, 0, 'e');
  //  setWall(1, 0, 'e');
  //  setWall(2, 0, 'n');
  //  setWall(3, 0, 'n');
  printArray();
}

int LeftSideWall = 255;
int RightSideWall = 430;

void loop() {
  /*
    MoveForward();
    TurnRight();
    MoveForward();
    MoveForward();
    MoveForward();
    TurnRight();
    TurnRight();
    MoveForward();
    MoveForward();
    TurnLeft();
    MoveForward();
    TurnLeft();
    TurnLeft();
    MoveForward();
    TurnLeft();
    MoveForward();
    TurnLeft();
    MoveForward();
    TurnRight();
    TurnRight();
    delay(5000);*/


  Serial.println("Start");
  //  printMap();
  //  printArray();
  //  setWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir+1));
  //  printMap();
  first_Search();
  //  scan();
  printMap();
  printArray();
  first_Search();
  printMap();
  printArray();

  //  TurnLeft(); TurnRight();  //victory dance
  while (true);
}
