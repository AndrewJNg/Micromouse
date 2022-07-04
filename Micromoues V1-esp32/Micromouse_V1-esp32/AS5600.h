#include <Wire.h>

void encoder_setup();
void AS5600_I2C_setup_1();
void AS5600_I2C_setup_2();

int AS5600_I2C_update_1();
int AS5600_I2C_update_2();
// Left encoder I2C pins
#define SDA_1 21
#define SCL_1 22

// Right encoder I2C pins
#define SDA_2 18
#define SCL_2 19

//TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

void encoder_setup()
{
  AS5600_I2C_setup_1();
  AS5600_I2C_setup_2();
}

void AS5600_I2C_setup_1()
{
  Wire.begin(SDA_1, SCL_1, 400000);
  delay(5);
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x01));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x03));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x04));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x07));
  Wire.write(byte(0x23));
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x08));
  Wire.write(byte(0xE3));
  Wire.endTransmission();
  delay(5);
}

void AS5600_I2C_setup_2()
{
  I2Ctwo.begin(SDA_2, SCL_2, 400000);

  delay(5);
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x01));
  I2Ctwo.write(byte(0x00));
  I2Ctwo.endTransmission();
  delay(5);
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x02));
  I2Ctwo.write(byte(0x00));
  I2Ctwo.endTransmission();
  delay(5);

  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x03));
  I2Ctwo.write(byte(0x00));
  I2Ctwo.endTransmission();
  delay(5);
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x04));
  I2Ctwo.write(byte(0x00));
  I2Ctwo.endTransmission();
  delay(5);

  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x07));
  I2Ctwo.write(byte(0x23));
  I2Ctwo.endTransmission();
  delay(5);

  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x08));
  I2Ctwo.write(byte(0xE3));
  I2Ctwo.endTransmission();
  delay(5);
}

int AS5600_I2C_update_1()
{

  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0X0C));
  Wire.endTransmission();
  Wire.requestFrom(byte(0x36), 2);
  while (Wire.available() < 2) ;


  int high = Wire.read();
  int low = Wire.read();
  int value = ( high << 8 ) | low;

  //invert direction
  value = 4095 - value;
  return value;
}


int AS5600_I2C_update_2()
{

  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0X0C));
  I2Ctwo.endTransmission();
  I2Ctwo.requestFrom(byte(0x36), 2);
  while ( I2Ctwo.available() < 2);


  int high =  I2Ctwo.read();
  int low =  I2Ctwo.read();
  int value = ( high << 8 ) | low;

  //invert direction
  //  value = 4095 - value;
  return value;
}


double currAngle[2] = {0, 0};
//unsigned long enc_menu_prevMillis = 0;

void enc_menu_update()
{
  static double prevAngle[2] = {0, 0};
  static int multiplyAngle[2] = {0, 0};

  currAngle[0] = ((double) map(AS5600_I2C_update_1(), 0, 4095, -18000, 18000) / 100);
  currAngle[1] = ((double) map(AS5600_I2C_update_2(), 0, 4095, -18000, 18000) / 100);

  for (int i = 0; i < 2; i++)
  {
    if ((prevAngle[i] > 90 && prevAngle[i]  < 180  ) && ( currAngle[i]  > -180 &&  currAngle[i]  < -90)  ) multiplyAngle[i]++;
    else if ((prevAngle[i]  > -180 &&  prevAngle[i]  < -90) && (currAngle[i]  > 90 && currAngle[i]  < 180)  ) multiplyAngle[i]--;
    prevAngle[i]  = currAngle[i] ;

    currAngle[i]  = currAngle[i]  + multiplyAngle[i]  * 360;
  }

}


bool motorForward[2] = {true, true};

void enc_motor_update()
{
  static double prevAngle[2] = {0, 0};
  static int multiplyAngle[2] = {0, 0};

  currAngle[0] = ((double) map(AS5600_I2C_update_1(), 0, 4095, -18000, 18000) / 100);
  currAngle[1] = ((double) map(AS5600_I2C_update_2(), 0, 4095, -18000, 18000) / 100);

  for (int i = 0; i < 2; i++)
  {

    if (currAngle[i] < (prevAngle[i] - 50))
    {
      if (motorForward[i] == true)
      {
        multiplyAngle[i]++;
      }
    }

    if (currAngle[i] > ( prevAngle[i] + 50))
    {
      if (motorForward[i] == false)
      {
        multiplyAngle[i]--;
      }

    }
    prevAngle[i]  = currAngle[i] ;
    currAngle[i]  = currAngle[i]  + multiplyAngle[i]  * 360;
  }

}




//double encValLeft()
//{
//  static double prevAngle = 0;
//  static int multiplyAngle = 0;
//
//  // obtain absolute Z angle from start
//  double currAngle = ((double) map(AS5600_I2C_update_1(), 0, 4095, -18000, 18000) / 100); //ypr[0] * 180 / M_PI;
//
//  if ((prevAngle > 90 && prevAngle < 180  ) && ( currAngle > -180 &&  currAngle < -90)  ) multiplyAngle ++;
//  else if ((prevAngle > -180 &&  prevAngle < -90) && (currAngle > 90 && currAngle < 180)  ) multiplyAngle --;
//  prevAngle = currAngle;
//
//  currAngle = currAngle + multiplyAngle * 360;
//  return currAngle;
//}
//
//double encValRight()
//{
//  static double prevAngle = 0;
//  static int multiplyAngle = 0;
//
//  // obtain absolute Z angle from start
//  double currAngle =  ((double)map(AS5600_I2C_update_2(), 0, 4095, -18000, 18000) / 100); // * 180 / M_PI;
//
//  if ((prevAngle > 90 && prevAngle < 180  ) && ( currAngle > -180 &&  currAngle < -90)  ) multiplyAngle ++;
//  else if ((prevAngle > -180 &&  prevAngle < -90) && (currAngle > 90 && currAngle < 180)  ) multiplyAngle --;
//  prevAngle = currAngle;
//
//  currAngle = currAngle + multiplyAngle * 360;
//  return currAngle;
//}


//int enc_update()
//{
//  int leftRaw = AS5600_I2C_update_1();
//  int rightRaw = AS5600_I2C_update_2();
//
//
//  return
//}
