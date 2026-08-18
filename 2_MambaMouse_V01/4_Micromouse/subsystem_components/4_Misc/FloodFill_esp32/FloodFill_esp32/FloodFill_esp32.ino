void system();
double startPoint = 0;
double endPoint = 0;
int Mode = 1;// set mode 1 as default
boolean Start = false;
unsigned long StartTimer = 0;


#include "Movement.h"
#include "OLED.h"
#include "FloodFill.h"

void setup() {
  Serial.begin(115200);
  Motor_setup();
  motor(0, 0);
  OLED_setup();

  FloodFill_setup();

  setWall(0, 0, 'e');
  setWall(0, 1, 'n');
  
  setWall(1, 1, 'n');
  setWall(1, 1, 'e');
  
  setWall(2, 0, 'e');
  setWall(2, 1, 'e');
  
  setWall(3, 2, 'e');
  setWall(3, 1, 'e');
  printMap() ;
  
//  flood_fill(target_X, target_Y, 1);
  first_Search();
}

void loop() {
  // put your main code here, to run repeatedly:

//  printMap() ;
//    flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
}

void system()
{
}
