/*
This is for a cheap but capable maze solving robot (below RM200) with sufficient hardware to perform high level speed control 
- ESP32-WROOM microcontroller with bluetooth capabilities for wireless control with PS3
- 12 bit magnetic encoder (AS5600 - I2C)
- 650RPM N20 motors
- TB6612FNG motor driver
- 6 IR sensor pairs (TEFT4300 phototransistor, TSAL4400 emitter) 
- MPU6050 gyroscope (I2C)
- OLED display (I2C)

Written by Andrew Joseph Ng (AndrewJNg)
*/
// #define PS3_enable 0
#define bluetooth_serial_enable 1

// function prototypes
void setup();
void loop();
void system();

int Mode = 1;  // set mode 1 as default
int Start = true;

unsigned long StartTimer = 0;

// Sensor libraries
#include <Wire.h>
#include "Bluetooth_Serial.h"

#include "Infrared.h"
#include "MPU6050.h"
#include "Motor_Subsystem.h"

// Advance libraries
#include "Memory.h"  // store IR values

// User interface libraries
#include "User_interface.h"
#include "OLED.h"

// #include "FloodFill.h"

void setup() {

  Serial.begin(115200);
  // BT_setup();
  motor_subsystem_setup();

  // Gyro_setup();
  // IR_setup();
  // read_memory();
  OLED_setup();

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

      // leftMotor.resetPID();
      // rightMotor.resetPID();
      leftMotor.current_batt_voltage = voltage_level();
      rightMotor.current_batt_voltage = voltage_level();

      static double target_pos = 0;
      static unsigned long previousTargetChange = 0;
      double curr_distance_left = 0;
      double curr_distance_right = 0;

      while (true) {
        // system();
        // OLED_display_stats();
        leftMotor.setSpeed(300);
        // rightMotor.setSpeed(300);

        // curr_distance_left = leftMotor.angle2mm();
        // curr_distance_right = rightMotor.angle2mm();

        // // Timer variables

        // // Check if 5 seconds have passed
        // if (millis() - previousTargetChange >= 5000) {

        //   previousTargetChange = millis();

        //   // Toggle between 0 mm and 1000 mm
        //   if (target_pos == 0) {
        //     target_pos = 150;
        //   } else {
        //     target_pos = 0;
        //   }
        // }
        // Run position control
        // double Volt_signal_left = leftMotor.PD_Control(target_pos, curr_distance_left);
        // leftMotor.setMotorVolt(Volt_signal_left);

        // double Volt_signal_right = rightMotor.PD_Control(target_pos, curr_distance_right);
        // rightMotor.setMotorVolt(Volt_signal_right);
      }




    } else if (Mode == 2) {  // Speed Run
      leftMotor.current_batt_voltage = voltage_level();
      rightMotor.current_batt_voltage = voltage_level();
      // generateStepResponse();
      Start = 0;
      // rightMotor.setSpeed(500);
      // align_to_front_wall();


      // printMap();
      // first_Search();
      // Start = false;

      //  straight(100, 180 * 1);




    } else if (Mode == 3) {  // Calibration

      MotionParameters motionParams;
      MotionParameters motionParams2;
      // motionParams = leftMotor.calculateTrapezoidalProfile(180, 300, 200);
      // motionParams2 = rightMotor.calculateTrapezoidalProfile(180, 300, 200);

      Serial.println("Start");
      // leftMotor.resetPID();
      // rightMotor.resetPID();
      leftMotor.current_batt_voltage = voltage_level();
      rightMotor.current_batt_voltage = voltage_level();
      double start_left = leftMotor.angle2mm();
      double start_right = rightMotor.angle2mm();
      while ((motionParams.time_step < (motionParams.T)) && Start == 1) {

        // while(1){
        // Serial.print("  ");
        // Serial.print(motionParams.prev_time);
        // Serial.print("  ");
        // Serial.print(motionParams.time_step);
        // Serial.print("  ");
        // Serial.print(motionParams.T);
        // Serial.println("  ");
        // leftMotor.followProfile(&motionParams);
        // rightMotor.followProfile(&motionParams2);
        system();
        OLED_display_stats();
      }

      SerialBT.println(leftMotor.angle2mm() - start_left);
      SerialBT.println(rightMotor.angle2mm() - start_right);
      Serial.println("End");
      Start = 0;


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
      read_walls();

      // int Speed = map(PS3_LeftAnalogStickSpeed(stick_LY), -255, 255, -4000, 4000);
      // int Diff = map(PS3_LeftAnalogStickSpeed(stick_RX), -255, 255, -4000, 4000);

      int Speed = 0;
      int Diff = 0;
      // rpmMove(Speed + Diff, Speed - Diff);
      // motor(Speed + Diff, Speed - Diff);
      // motor(0,0);
    }
  } else {  // Menu operation

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
  // IR_update();
  // Gyro_update();
}
