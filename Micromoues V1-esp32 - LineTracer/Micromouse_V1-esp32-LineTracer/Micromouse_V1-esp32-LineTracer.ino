// installation links


/////////////////////////////////////////////////////////////////////////////////////////////////////////

// function prototypes
void setup();
void loop();
void system();
void read_memory();
void bluetooth_setup();
void bluetooth_loop();
// void Junction(int speed_junction, float kp, float ki, float kd, char type, char action);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// global variables

double startPoint = 0;
double endPoint = 0;
int Mode = 1;  // set mode 1 as default
bool Start = false;
unsigned long StartTimer = 0;

//double Kp = 1.8, Ki = 1.8, Kd = 0.12;
//double Kp = 5, Ki = 4.5, Kd = 0.03;
double Kp = 5, Ki = 5.1, Kd = 0.03;

//double turnKp = 2, turnKi = 0, turnKd = 0.000;
//double turnKp = 1, turnKi = 2, turnKd = 0.001;
double turnKp = 1, turnKi = 2, turnKd = 0.0001;

double straightKp = 1, straightKi = 0, straightKd = 0;

double rpmSetLeft, InputRpmLeft, OutputLeftMotor;
double rpmSetRight, InputRpmRight, OutputRightMotor;
double turnSetpoint, turnInput, turnOutput;
double straightSetpoint, straightInput, straightOutput;

double lineKp = 3, lineKi = 0.001, lineKd = 0.04;
// double lineKp = 3.0, lineKi = 0, lineKd = 0.40;
double lineSetpoint, lineInput, lineOutput;


int runSpeed = 80;
int turnSpeed = 80;

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "Infrared.h"
// #include "AS5600.h"
#include "MPU6050.h"
#include "Movement.h"
#include "PID.h"

// #include "Speed_profile.h"
#include "PS3.h"

#include "User_interface.h"
#include "OLED.h"
// bool Phone = true;
bool Phone = false;

void setup() {
  // Serial.begin(115200);
  read_memory();
  Motor_setup();
  OLED_setup();

  IR_setup();
  if (Phone == true)
    bluetooth_setup();
  else
    PS3_setup();

  PID_setup();
  // Enc_setup();
  // Gyro_setup();
}

String my_list;
int commandSeq[30];
int commandStep = 0;

void loop() {
  system();

  if (Start) {
    if (Mode == 1) {
      // Junction(runSpeed, lineKp, lineKi, lineKd, 'L', 'L');
      // Start = false;
      // // Junction(runSpeed, lineKp, lineKi, lineKd, 'L', 'L');
      // // Start = false;
      // /*
      Serial.println("Start");
      for (int i = 0; i < sizeof(commandSeq) / 4; i++) {

        switch (commandSeq[i]) {
          case 1:  //Left
            Serial.print("L ");
            SerialBT.write('L');
            Junction(runSpeed, lineKp, lineKi, lineKd, 'L', 'L');
            motor(0, 0);
            delay(500);
            break;

          case 2:  // Ignore
            Serial.print("I ");
            SerialBT.write('I');
            Junction(runSpeed, lineKp, lineKi, lineKd, 'M', 'I');
            motor(0, 0);
            delay(500);
            break;

          case 3:  // Right
            Serial.print("R ");
            SerialBT.write('R');
            Junction(runSpeed, lineKp, lineKi, lineKd, 'R', 'R');
            motor(0, 0);
            delay(500);
            break;

          case 4:  // Stop
            Serial.print("s ");
            SerialBT.write('s');
            Junction(runSpeed, lineKp, lineKi, lineKd, 'R', 's');
            motor(0, 0);
            delay(500);
            break;

          default:  //Stop
            // Serial.print("s ");
            // Junction(runSpeed, lineKp, lineKi, lineKd, 'R', 's');
            break;
        }
      }
      for (int i = 0; i < sizeof(commandSeq) / 4; i++) {
        commandSeq[i] = 0;
      }
      commandStep = 0;

      motor(0, 0);
      Start = 0;
      delay(1000);
      // */

    } else if (Mode == 2) {
      // PID(runSpeed, lineKp, lineKi, lineKd);
      Junction(runSpeed, lineKp, lineKi, lineKd, 'R', 'R');
      Start = false;
    } else if (Mode == 3) {  // Calibration
      calibration();
    } else if (Mode == 4) {  // PS3 movement
      OLED_display_stats();
      // motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
      if (Phone == true) {

      }
      // motor();
      else {
        motor(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY), PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
      }
    }


  }

  else {
    motor(0, 0);
    OLED_menu_display();

    if (Mode > 4) Mode = 1;
    else if (Mode < 1) Mode = 4;
  }
}

//system functions, important to keep different time sensitive functions working
void system() {
  IR_update();
  // Gyro_update();
  if (Phone == true)
    bluetooth_loop();
}
