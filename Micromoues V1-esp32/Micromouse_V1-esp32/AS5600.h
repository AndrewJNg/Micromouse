#include <Wire.h>

// Left encoder I2C pins
#define SDA_1 21
#define SCL_1 22

// Right encoder I2C pins
#define SDA_2 18
#define SCL_2 19

//TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

// function prototypes
// setup
void Enc_setup();
void AS5600_I2C_setup_1();
void AS5600_I2C_setup_2();

// encoder updating
int AS5600_I2C_update_1();
int AS5600_I2C_update_2();
void enc_menu_update();
void enc_motor_update();

// encoder calculation
double encDistance(int returnNum);
double encSpeed(int returnNum);

//g lobal functions used
double currAngle[2] = {0, 0};
bool motorForward[2] = {true, true};

void Enc_setup()
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
  //  Wire.write(byte(0x23));
  I2Ctwo.write(byte(0x3F));
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
  //  I2Ctwo.write(byte(0x23));
  I2Ctwo.write(byte(0x3F));
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


//unsigned long enc_menu_prevMillis = 0;

void enc_menu_update()
{
  static double prevAngle[2] = {0, 0};
  static int multiplyAngle[2] = {0, 0};

  //  currAngle[0] = ((double) map(AS5600_I2C_update_1(), 0, 4095, -18000, 18000) / 100);
  //  currAngle[1] = ((double) map(AS5600_I2C_update_2(), 0, 4095, -18000, 18000) / 100);
  currAngle[0] = AS5600_I2C_update_1();
  currAngle[1] = AS5600_I2C_update_2();
  //Serial.print(currAngle[0]);
  //Serial.print("   ");
  //Serial.print(currAngle[1]);
  //Serial.print("   ");
  for (int i = 0; i < 2; i++)
  {
    //    if ((prevAngle[i] > 90 && prevAngle[i]  < 180  ) && ( currAngle[i]  > -180 &&  currAngle[i]  < -90)  ) multiplyAngle[i]++;
    //    else if ((prevAngle[i]  > -180 &&  prevAngle[i]  < -90) && (currAngle[i]  > 90 && currAngle[i]  < 180)  ) multiplyAngle[i]--;
    //    prevAngle[i]  = currAngle[i] ;
    //
    //    currAngle[i]  = currAngle[i]  + multiplyAngle[i]  * 360;
    //    0 = -180
    //    1024 = -90
    //    2048 = 0
    //    3072 = 90
    //    4096 = 180
    //    if ((prevAngle[i] > 2560 && prevAngle[i]  < 4096  ) && ( currAngle[i]  >  0 &&  currAngle[i]  < 1536 )  ) multiplyAngle[i]++;
    //    else if ((prevAngle[i]  >  0 &&  prevAngle[i]  < 1536 ) && (currAngle[i]  > 2560 && currAngle[i]  < 4096)  ) multiplyAngle[i]--;
    if ((prevAngle[i] > 3072 && prevAngle[i]  < 4096  ) && ( currAngle[i]  >  0 &&  currAngle[i]  < 1024 )  ) multiplyAngle[i]++;
    else if ((prevAngle[i]  >  0 &&  prevAngle[i]  < 1024 ) && (currAngle[i]  > 3072 && currAngle[i]  < 4096)  ) multiplyAngle[i]--;
    prevAngle[i]  = currAngle[i] ;

    currAngle[i]  = currAngle[i]  + multiplyAngle[i]  * 4096;
  }

  //Serial.print(currAngle[0]);
  //Serial.print("   ");
  //Serial.print(currAngle[1]);
  //Serial.println("   ");
}



void enc_motor_update()
{
  //  static unsigned long prevMillis = 0;
  //  prevMillis = micros();
  //  Serial.print("encoder:");
  //  Serial.print(micros()-prevMillis);


  static double prevAngle[2] = {0, 0};
  static int multiplyAngle[2] = {0, 0};

  //  currAngle[0] = ((double) map(AS5600_I2C_update_1(), 0, 4095, -18000, 18000) / 100);
  //  currAngle[1] = ((double) map(AS5600_I2C_update_2(), 0, 4095, -18000, 18000) / 100);
  currAngle[0] = AS5600_I2C_update_1();
  currAngle[1] = AS5600_I2C_update_2();

  for (int i = 0; i < 2; i++)
  {

    if (currAngle[i] < (prevAngle[i] - 100))
    {
      if (motorForward[i] == true)
      {
        multiplyAngle[i]++;
      }
    }

    if (currAngle[i] > ( prevAngle[i] + 100))
    {
      if (motorForward[i] == false)
      {
        multiplyAngle[i]--;
      }

    }
    prevAngle[i]  = currAngle[i] ;
    currAngle[i]  = currAngle[i]  + multiplyAngle[i]  * 4096;
  }

  //  Serial.print("encoder:");
  //  Serial.print(micros()-prevMillis);

}

double encDistance(int returnNum)
{
  const float radius = 17; //34mm in diameter
  const float pi = 3.142;

  double degree[2] = {0, 0};
  double distance[2] = {0, 0};
  //  enc_motor_update();


  degree[0] = (double)currAngle[0] * 360 / 4096;
  degree[1] = (double)currAngle[1] * 360 / 4096;


  distance[0] = (2 * pi * radius * degree[0]) / 360;
  distance[1] = (2 * pi * radius * degree[1]) / 360;
  //Serial.print(degree[0]);
  //Serial.print("  ");
  //Serial.println(distance);
  return distance[returnNum];


}

double encSpeed(int returnNum)
{
  static unsigned long prevMillis[2] = {0, 0};
  static double prevDistance[2] = {0, 0};
  static double Speed[2] = {0, 0};

  enc_motor_update();

  double currDistance = encDistance(returnNum);
  double diff =   currDistance - prevDistance[returnNum];

  if (abs(diff) > 0)
  {
    prevDistance[returnNum] =  currDistance;
    //      Serial.print("diff: ");
    //      Serial.print(diff);

    //      Serial.print(" time: ");
    //      Serial.print(millis() - prevMillis[returnNum]);
    Speed[returnNum] = (diff * 1000) / ((millis() - prevMillis[returnNum])); // * 100;

    //      Serial.print(" speed: ");
    //      Serial.println(Speed[returnNum]);
    prevMillis[returnNum] = millis();
  }
  //    else
  //    {
  //      Speed[returnNum] =0;
  //    }


  //  if ((millis() - prevMillis) > 100)
  //  {
  //    prevDistance =  currDistance;
  //    Serial.print("diff: ");
  //    Serial.print(diff);
  //
  //    Serial.print(" time: ");
  //    Serial.print(millis() - prevMillis);
  //    Speed = (diff * 1000) / ((millis() - prevMillis)); // * 100;
  //
  //    Serial.print(" speed: ");
  //    Serial.println(Speed);
  //    prevMillis = millis();
  //  }


  //    Serial.print(micros()-prevMillis);
  return Speed[returnNum];
}
