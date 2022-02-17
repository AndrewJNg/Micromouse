/*
 * 
 *  Arduino Maze Solver 
 *    - arush15june 20/12/17
 *  https://github.com/arush15june/arduino-maze-solver
 */

#include "DifferentialDrive.h"
#include "LDRLineSensor.h"

// Enums and Structs
enum MODE {
    MAP, // Maze Mapping Mode
    SOLVE // Maze Solving Mode
};

// Pin Definitions

// This pin is the button which changes the modes between MAP and FIND
// If this is high during setup(), then mode is changed to FIND else it 
// is MAP by default

#define pinBotMode 1

// DD Config
// DifferentialDrive( pins[rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB], rightDefaultSpeed, leftDefaultSpeed )

#define rightMotorEnable 0
#define rightMotorDirF 0
#define rightMotorDirB 0

#define leftMotorEnable 0
#define leftMotorDirF 0
#define leftMotorDirB 0

#define rightDefaultSpeed 0
#define leftDefaultSpeed 0

// LDR Sensor Array
#define noOfSensors 5

#define sensorPin1 0
#define sensorPin1Min 0
#define sensorPin1Max 0

#define sensorPin2 0
#define sensorPin2Min 0
#define sensorPin2Max 0

#define sensorPin3 0
#define sensorPin3Min 0
#define sensorPin3Max 0

#define sensorPin4 0
#define sensorPin4Min 0
#define sensorPin4Max 0

#define sensorPin5 0
#define sensorPin5Min 0
#define sensorPin5Max 0
// define all the sensor pins: #define sensorsPin<sensorNo>


// Global Variables

int DD_pins[] = {rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB};
DifferentialDrive dd(DD_pins, rightDefaultSpeed, leftDefaultSpeed); 

int LDR_Pins[] = {sensorPin1, sensorPin2, sensorPin3, sensorPin4, sensorPin5};
int LDR_Ranges[][2] = { 
    {sensorPin1Min, sensorPin1Max},
    {sensorPin2Min, sensorPin2Max},
    {sensorPin3Min, sensorPin3Max},
    {sensorPin4Min, sensorPin4Max},
    {sensorPin5Min, sensorPin5Max},
};
LineSensor LDR(noOfSensors, LDR_Pins, LDR_Ranges);

void setup() {
    pinMode(pinBotMode, INPUT);
    MODE mode = digitalRead(pinBotMode);
    Serial.begin(9600);
    Serial.println("Initializing Bot");
    Serial.println("Mode:"+(mode ? String("MAPPING") : String("SOLVING")));
}

void loop() {

  direction go = LDR.find(); 

  if(go == STOP || go == UNKNOWN) {
    Serial.println("STOP bot");
    dd.stop();
  }
  else if(go == FORWARD) {
    Serial.println("Going Forward");
    dd.forward();
  }
  else if(go == LEFT) {
    Serial.print("Going LEFT");
    dd.stop();
    while(LDR.find() != FORWARD) {
      dd.left();
    }
  }
  else if(go == RIGHT) {
    Serial.println("Going RIGHT");
    dd.stop();
    while(LDR.find() != FORWARD) {
      dd.right();
    }
  }

}
