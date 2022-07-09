
float v1Filt = 0;
float v1Prev = 0;
float v2Filt = 0;
float v2Prev = 0;

int prevCountLeft = 0;
int prevCountRight = 0;
unsigned long prevMicro = 0;
unsigned long EncprevMicro = 0;

void rpmMove(float target_rpm_left, float target_rpm_right)
{

  enc_motor_update();
  int interval = 1000;
  unsigned long timeDIff = micros() - EncprevMicro;


  if (timeDIff >= interval) {

    float rpmLeft = (float)((currAngle[0] - prevCountLeft) * (1.0 / ((float)timeDIff * 1e-6)) * 60) / 4096;
    float rpmRight = (float)((currAngle[1] - prevCountRight ) * (1.0 / ((float)timeDIff * 1e-6)) * 60) / 4096;
    prevCountLeft = currAngle[0];
    prevCountRight = currAngle[1];
    EncprevMicro = micros();

    float v1 = rpmLeft;

    //        v1Filt =0.99937188*v1Filt + 0.00031406*v1+0.00031406*v1Prev;  //0.1 hz
    //        v1Filt =0.99686333*v1Filt + 0.00156833*v1+0.00156833*v1Prev;  //0.5 hz
    v1Filt = 0.98751209 * v1Filt + 0.00624395 * v1 + 0.00624395 * v1Prev; //2 hz
    //        v1Filt = 0.854*v1Filt + 0.0728*v1+0.0828*v1Prev;            //5 hz
    v1Prev = v1;

    float v2 = rpmRight;
    v2Filt = 0.98751209 * v2Filt + 0.00624395 * v2 + 0.00624395 * v2Prev;;
    v2Prev = v2;

    InputRpmLeft = v1Filt;
    rpmSetLeft = target_rpm_left;
    leftMotorVel.SetTunings(Kp, Ki, Kd);
    leftMotorVel.Compute();
    int SpeedLeft = OutputLeftMotor;

    InputRpmRight = v2Filt;
    rpmSetRight = target_rpm_right;
    rightMotorVel.SetTunings(Kp, Ki, Kd);
    rightMotorVel.Compute();
    int SpeedRight = OutputRightMotor;


    motor(SpeedLeft, SpeedRight);

    Serial.print(v1Filt, 0);
    Serial.print("  ");
    Serial.print(v2Filt, 0);
    Serial.print("  ");
    Serial.print(target_rpm_left, 0);
    Serial.print("  ");
    Serial.print(target_rpm_right, 0);
    Serial.print("  ");
    Serial.print(0, 0);
    Serial.print("  ");
    Serial.print(900, 0);
    Serial.println();

  }
}
