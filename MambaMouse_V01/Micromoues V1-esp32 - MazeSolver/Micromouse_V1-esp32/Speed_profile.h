
int prevCountLeft = 0;
int prevCountRight = 0;
unsigned long EncPrevMicro = 0;

//low pass filter at 5Hz, sample at 1kHz
LowPass<1> lpLeft(5, 1e3, true);
LowPass<1> lpRight(5, 1e3, true); 

void rpmMove(float target_rpm_left, float target_rpm_right) {

  enc_motor_update();
  int interval_micro = 1000; // 1000 microsecond
  unsigned long timeDIff = micros() - EncPrevMicro;

  if (timeDIff >= interval_micro) {
    EncPrevMicro = micros();

    // convert motor encoder counts to rpm
    float rpmLeft = (float)((currAngle[0] - prevCountLeft) * (1.0 / ((float)timeDIff * 1e-6)) * 60) / 4096;
    float rpmRight = (float)((currAngle[1] - prevCountRight) * (1.0 / ((float)timeDIff * 1e-6)) * 60) / 4096;
    prevCountLeft = currAngle[0];
    prevCountRight = currAngle[1];
    
    // apply filter to the signal
    float v1Filt = lpLeft.filt(rpmLeft);
    float v2Filt = lpRight.filt(rpmRight);

    
    // apply PID tuning
    InputRpmLeft = v1Filt;
    rpmSetLeft = target_rpm_left;
    leftMotorVel.SetTunings(KpLeft, KiLeft, KdLeft);
    leftMotorVel.Compute();
    double SpeedLeft = OutputLeftMotor;

    InputRpmRight = v2Filt;
    rpmSetRight = target_rpm_right;
    rightMotorVel.SetTunings(KpRight, KiRight, KdRight);
    rightMotorVel.Compute();
    double SpeedRight = OutputRightMotor;

    // apply speed to motor drivers
    // motor(SpeedLeft, SpeedRight);
    motor(SpeedLeft, 0);
    // motor(0, 0);


    Serial.print(SpeedLeft, 0);
    Serial.print("\t");
    // Serial.print(SpeedRight, 0);
    // Serial.print("\t");

    Serial.print(rpmLeft, 0);
    Serial.print("\t");
    // Serial.print(rpmRight, 0);
    // Serial.print("\t");

    // Serial.print(v1Filt, 0);
    // Serial.print("\t");
    // Serial.print(v2Filt, 0);
    // Serial.print("\t");
    Serial.print(target_rpm_left, 0);
    Serial.print("\t");
    // Serial.print(target_rpm_right, 0);
    // Serial.print("\t");
    Serial.print(0, 0);
    Serial.print("\t");
    Serial.print(900, 0);
    Serial.println();

    
  }
}

