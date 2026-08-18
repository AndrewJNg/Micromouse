// Functions related to line following algorithmns

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// LinePosition is to obtain a numerical value of where the line is compared to the robot
float last_Position = 0;
float LinePostition() {

  // initiate local variables
  int sum_state = 0;
  int get_Pos = 0;
  float Position = 0;

  // count number of sensors detecting the line
  for (int i = 0; i < sizeof(IRRecPin); i++)
    sum_state += get_state[i];

  // if non of the sensors detect the line
  if (sum_state == 0) {

    if (last_Position < 0)  //last seen on the left sensor
      return -2000;
    else  //last seen on the right sensor
      return 2000;
  }

  // when at least 1 sensor sees the line, calculate the position value & add it to last known location
  else {

    // multiply by weightage value
    for (int i = 0; i < sizeof(IRRecPin); i++)
      get_Pos = get_Pos + (((int)get_state[i] * (i * 10 - 20)));

    // calculate position value & save it as last known valid location
    Position = (float)get_Pos / sum_state;
    last_Position = Position;
  }

  return Position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void PID(int speed_PID, float kp, float ki, float kd) {

  // obtain line position and target position
  lineInput = LinePostition();
  lineSetpoint = 0;
  int SpeedDiff = 0;

  if (lineInput == -2000)
    motor(0, speed_PID);

  else if (lineInput == 2000)
    motor(speed_PID, 0);

  else {
    // do PID calculations
    linePID.SetTunings(kp, ki, kd);
    linePID.Compute();
    SpeedDiff = lineOutput;

    // run motor
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
  }

  // OLED display stats
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
  OLED.display();
}