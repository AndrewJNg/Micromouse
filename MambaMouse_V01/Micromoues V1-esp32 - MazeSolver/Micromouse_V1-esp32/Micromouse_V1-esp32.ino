/*
This is for a cheap but capable maze solving robot (below RM200) with sufficient hardware to perform high level speed control 
- ESP32 microcontroller with bluetooth capabilities for wireless control with PS3
- 12 bit magnetic encoder (AS5600 - I2C)
- 600RPM N20 motors
- TB6612FNG motor driver
- 6 IR sensor pairs (TEFT4300 phototransistor, TSAL4400 emitter) 
- MPU6050 gyroscope (I2C)
- OLED display (I2C)

Written by Andrew Joseph Ng (AndrewJNg)
*/

// function prototypes
void setup();
void loop();
void system();

int Mode = 1;  // set mode 1 as default
int Start = false;

unsigned long StartTimer = 0;

//double Kp = 1.8, Ki = 1.8, Kd = 0.12;
//double Kp = 5, Ki = 4.5, Kd = 0.03;
double KpLeft = 10, KiLeft = 0, KdLeft = 0.00;
double KpRight = 5, KiRight = 5.1, KdRight = 0.03;

//double turnKp = 2, turnKi = 0, turnKd = 0.000;
//double turnKp = 1, turnKi = 2, turnKd = 0.001;
// double turnKp = 1, turnKi = 2, turnKd = 0.0001;
// double turnKp = 1, turnKi = 0, turnKd = 0.0000;

double straightKp = 1, straightKi = 0, straightKd = 0;

double rpmSetLeft, InputRpmLeft, OutputLeftMotor;
double rpmSetRight, InputRpmRight, OutputRightMotor;
double turnSetpoint, turnInput, turnOutput;
double straightSetpoint, straightInput, straightOutput;

int leftWall = 50;
int rightWall = 50;
#include <Wire.h>

#include "Infrared.h"
#include "MPU6050.h"
#include "Motor_Subsystem.h"

#include "Memory.h"  // store IR values

// #include "PID.h"

#include "lowPass.h"
// #include "Speed_profile.h"
// #include "Cell_movement.h"
#include "PS3.h"

#include "User_interface.h"
#include "OLED.h"

// #include "FloodFill.h"

void setup() {

  Serial.begin(115200);
  
  motor_subsystem_setup();
  
  PS3_setup();
  OLED_setup();
  
  IR_setup();
  read_memory();
  Gyro_setup();
  
  
  
  // PID_setup();
  // FloodFill_setup();
  
  }



void loop() {
  system();
  
  if (Start) {
    if (Mode == 1) {  // First search for new map
      // clearMap();
      // printMap();
      // first_Search();
      // Start = false;
      // leftMotor.setMotorSpeed(1500);
      // rightMotor.setMotorSpeed(1500);

      // delay(50);
      // Serial.print("leftMotor: ");
      // Serial.print(leftMotor.updateEncoder());
      // Serial.print("    rightMotor: ");
      // Serial.println(rightMotor.updateEncoder());

      // Serial.print("leftMotor: ");
      // Serial.print(leftMotor.angle_2_mm());
      // Serial.print("    rightMotor: ");
      // Serial.println(rightMotor.angle_2_mm());

    // leftMotor.PID_Kp = KpLeft;
    // leftMotor.PID_Ki = KiLeft;
    // leftMotor.PID_Kd = KdLeft;
    
    // rightMotor.PID_Kp = KpLeft;
    // rightMotor.PID_Ki = KiLeft;
    // rightMotor.PID_Kd = KdLeft;
//  leftMotor.setMotorPWM(4095);
//  rightMotor.setMotorPWM(4095);
      rightMotor.setSpeed(750);
      leftMotor.setSpeed(750);
      OLED_display_stats();




    } else if (Mode == 2) {  // Speed Run
      generateStepResponse();
      Start=0;
      // rightMotor.setSpeed(500);
      // align_to_front_wall();


      // printMap();
      // first_Search();
      // Start = false;

      //  straight(100, 180 * 1);




    } else if (Mode == 3) {  // Calibration
      // unsigned long IR_calibrate_start = millis();

      // // reset values
      // for (int i = 0; i < sizeof(IREmitPin); i++) {
      //   minIR[i] = 4095;
      //   maxIR[i] = 0;
      // }

      // // run calibration for 10 seconds
      // do {
      //   calibration();
      //   IR_update();
      //   OLED_display_stats();
      // } while ((millis() - IR_calibrate_start) <= 10000);

      // store_memory_IR();
      // Start = false;




    } else if (Mode == 4) {
      // PS3 movement
      OLED_display_stats();

      int Speed = map(PS3_LeftAnalogStickSpeed(stick_LY), -255, 255, -4000, 4000);
      int Diff = map(PS3_LeftAnalogStickSpeed(stick_RX), -255, 255, -4000, 4000);
      // rpmMove(Speed + Diff, Speed - Diff);
      // motor(Speed + Diff, Speed - Diff);
      // motor(0,0);
    }
  } else {// Menu operation
    
    leftMotor.stopMotor();
    rightMotor.stopMotor();

    OLED_menu_display();
    encoderMode();
    // IR_left_menu.count(left_IR_button(), &Mode, 1);
    IR_right_menu.count(right_IR_button(), &Start, 1);

    if (Mode > 4) Mode = 1;
    else if (Mode < 1) Mode = 4;
  }
}

void system() {
  //system functions, important to keep different time sensitive functions working
  IR_update();
  Gyro_update();
}
