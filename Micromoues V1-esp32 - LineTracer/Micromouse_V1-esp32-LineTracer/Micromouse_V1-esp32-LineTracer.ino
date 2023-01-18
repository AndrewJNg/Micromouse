// installation links


/////////////////////////////////////////////////////////////////////////////////////////////////////////

// function prototypes
void setup();
void loop();
void system();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// global variables

double startPoint = 0;
double endPoint = 0;
int Mode = 1;  // set mode 1 as default
boolean Start = false;
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

double lineKp = 2.8, lineKi = 0.001, lineKd = 0.04;
// double lineKp = 3.0, lineKi = 0, lineKd = 0.40;
double lineSetpoint, lineInput, lineOutput;


int runSpeed = 60;

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
#include "LineFollowing.h"


void setup() {
  // Serial.begin(115200);
  Motor_setup();
  OLED_setup();

  IR_setup();
  PS3_setup();

  PID_setup();
  // Enc_setup();
  // Gyro_setup();


  // FloodFill_setup();
}

void loop() {
  // IR_update();
  system();


  if (Start) {
    if (Mode == 1) {
      Junction(runSpeed, lineKp, lineKi, lineKd, 'L', 'L');
      motor(0,0);
      delay(1000);


    } else if (Mode == 2) {
      PID(runSpeed, lineKp, lineKi, lineKd);


    } else if (Mode == 3) {  // Mok's PID
      OLED.clearDisplay();

      OLED.setTextSize(1);
      OLED.setTextColor(SSD1306_WHITE);
      OLED.setCursor(0, 0);
      OLED.cp437(true);

      OLED.print("runSpeed: ");
      OLED.print(runSpeed);
      OLED.println("\t");
      OLED.print("lineKp: ");
      OLED.print(lineKp, 3);
      OLED.println("\t");
      OLED.print("lineKi: ");
      OLED.print(lineKi, 3);
      OLED.println("\t");
      OLED.print("lineKd: ");
      OLED.print(lineKd, 3);
      OLED.println("\t");

      OLED.display();  //update the display
      getLinePos(runSpeed, runSpeed, lineKp, lineKi, lineKd);



    } else if (Mode == 4) {  // PS3 movement
      OLED_display_stats();
      int Speed = PS3_LeftAnalogStickSpeed(stick_LX, stick_LY);
      motor(Speed, PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
    }
  } else {
    motor(0, 0);
    //rpmMove(0, 0);
    OLED_menu_display();
    //    IR_left_menu.count(left_IR_button(), &Mode, -1);
    //    IR_right_menu.count(right_IR_button(), &Mode, 1);
    if (Mode > 4) Mode = 1;
    else if (Mode < 1) Mode = 4;
  }
}

void system() {
  //system functions, important to keep different time sensitive functions working
  IR_update();
  // Gyro_update();
}
