
// const byte IRRecPin[5] = { 36, 39, 32, 34, 35 };

// byte IR[] = { A4, A5, A6, A7, A8, A9, A10, A11};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//  unsigned int getPosition = 0;

// void scanLine() {
//   for (int i = 0; i < (sizeof(IRRecPin)); i++) {
//     int valueIR = analogRead(IRRecPin[i]);
//     if (valueIR > 1500) {
//       get_state[i] = 1;
//     } else {
//       get_state[i] = 0;
//     }
//     // Serial.println(get_state[i]);
//     if (!whiteLine) {
//       get_state[i] = 1 - get_state[i];
//     }
//     // digitalWrite(led[i], get_state[i]);
//   }
// }

int error_old = 0;
int last_pos = 20;
int cum_error = 0;
unsigned long prev_pid_time = 0;

// int get_Pos(int IR_sensor[], int sensor_Num) {
//   IR_update();


//   for (int i = 0; i < sensors; i++) {
//     sum_state += get_state[i];
//   }

//   return -100;
// }

// leftMotorVel.SetTunings(Kp, Ki, Kd);
// leftMotorVel.Compute();
void getLinePos(int speedL_PID, int speedR_PID, float kp, float ki, float kd) {
  // scanLine();
  IR_update();
  getPosition = 0;
  int sum_state = 0;
  int sensors = 0;
  for (int i = 0; i < sizeof(IRRecPin); i++) {
    sensors++;
  }

  int midPos = 20;

  for (int i = 0; i < sensors; i++) {
    sum_state += get_state[i];
  }

  if (sum_state == 0) {

    if (last_pos >= midPos) {
      motor(100, 0);
      // motor(0, 0);
    }

    else if (last_pos < midPos) {
      motor(0, 100);
      // motor(0, 0);
    }

  }


  else {

    for (int i = 0; i < sensors; i++) {
      getPosition = getPosition + ((get_state[i] * (i + 1)) * 10);
    }
    getPosition = getPosition / sum_state;
    last_pos = getPosition;

    int error = getPosition - (midPos);
    cum_error = cum_error + error;
    // int speed_correction = kp * error + ki * (millis() - prev_pid_time) * cum_error + kd * (error - error_old);
    int speed_correction = kp * error + ki * (error - error_old);
    prev_pid_time = millis();
    error_old = error;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //motor control

    int speedL_ = speedL_PID + speed_correction;
    if (speedL_ < -255) {
      speedL_ = -255;
    } else if (speedL_ > 255) {
      speedL_ = 255;
    }


    int speedR_ = speedR_PID - speed_correction;
    if (speedR_ < -255) {
      speedR_ = -255;
    } else if (speedR_ > 255) {
      speedR_ = 255;
    }

    motor(speedL_, speedR_);
    //    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4])  + " "  + String(get_state[5])  + " " + String(get_state[6])  + " " + String(get_state[7])  + " " + String(getPosition));

    /*
    Serial.print(speed_correction);
    Serial.print("      ");
    Serial.print(speedL_);

    Serial.print("      ");
    Serial.println(speedR_);


    OLED.clearDisplay();

    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(0, 0);
    OLED.cp437(true);
    ;
    OLED.print(get_state[0]);
    OLED.print("\t");
    OLED.print(get_state[1]);
    OLED.print("\t");
    OLED.print(get_state[2]);
    OLED.print("\t");
    OLED.print(get_state[3]);
    OLED.print("\t");
    OLED.print(get_state[4]);
    OLED.print("\t");

    OLED.print("      ");
    OLED.println(speed_correction);
    // OLED.print(speed_correction);
    // OLED.print("      ");
    // OLED.print(speedL_);

    // OLED.print("      ");
    // OLED.println(speedR_);


    OLED.display();  //update the display
    */
  }
  //    Serial.println(getPosition);
}





float last_Position = 0;
float LinePostition() {
  // initiate local variables
  int sum_state = 0;
  int get_Pos = 0;
  float Position = 0;

  // count number of sensors detecting the line
  for (int i = 0; i < sizeof(IRRecPin); i++)
    sum_state += get_state[i];

  // make decision base on number of sensors seeing the line
  if (sum_state == 0) {  // when all sensors do not see the line, follow the last know location

    if (last_Position < 0)  //last seen on the left sensor
      Position = -20;
    else if (last_Position > 0)  //last seen on the right sensor
      Position = 20;
    else
      Position = 20;
  }

  else {  // when at least 1 sensor sees the line, calculate the position value & add it to last known location
    for (int i = 0; i < sizeof(IRRecPin); i++)
      get_Pos = get_Pos + (((int)get_state[i] * (i * 10 - 20)));

    Position = (float)get_Pos / sum_state;
    last_Position = Position;
  }

  /*
  Serial.print("sum_state: ");
  Serial.print(sum_state);
  Serial.print("\t");

  Serial.print("Position: ");
  Serial.print(Position);
  Serial.println();
  */
  return Position;
}


void PID(int speed_PID, float kp, float ki, float kd) {

  // int speed_PID = runSpeed;


  lineInput = LinePostition();
  lineSetpoint = 0;

  linePID.SetTunings(kp, ki, kd);
  linePID.Compute();
  int SpeedDiff = lineOutput;

  int speedL_ = speed_PID - SpeedDiff;
  if (speedL_ < -255) {
    speedL_ = -255;
  } else if (speedL_ > 255) {
    speedL_ = 255;
  }

  int speedR_ = speed_PID + SpeedDiff;
  if (speedR_ < -255) {
    speedR_ = -255;
  } else if (speedR_ > 255) {
    speedR_ = 255;
  }

  motor(speedL_, speedR_);


  OLED.clearDisplay();

  OLED.setTextSize(1);
  OLED.setTextColor(SSD1306_WHITE);
  OLED.setCursor(0, 0);
  OLED.cp437(true);

  OLED.print("runSpeed: ");
  OLED.print(speed_PID);
  OLED.println("\t");
  OLED.print("lineKp: ");
  OLED.print(kp, 3);
  OLED.println("\t");
  OLED.print("lineKi: ");
  OLED.print(ki, 3);
  OLED.println("\t");
  OLED.print("lineKd: ");
  OLED.print(kd, 3);
  OLED.println("\t");

  OLED.print("LinePosition: ");
  OLED.print(lineInput, 2);
  OLED.println("\t");
  OLED.print("SpeedDiff: ");
  OLED.print(SpeedDiff, DEC);
  OLED.println("\t");
  OLED.display();  //update the display
}