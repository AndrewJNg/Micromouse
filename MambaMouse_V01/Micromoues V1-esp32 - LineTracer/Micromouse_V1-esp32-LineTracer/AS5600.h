#include <Wire.h>

// Left encoder I2C pins
const byte SDA_1 =21;
const byte SCL_1 =22;

// Right encoder I2C pins
const byte SDA_2 =18;
const byte SCL_2 =19;

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

  // set start position (ZPOS) as 0 
  Wire.beginTransmission(byte(0x36));  
  Wire.write(byte(0x01));    // enter first ZPOS address
  Wire.write(byte(0x00));    // set as 0
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x02));     // enter second ZPOS address
  Wire.write(byte(0x00));     // set as 0
  Wire.endTransmission();
  delay(5);

  // set stop position (MPOS) as 0 
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x03));     // enter second MPOS address
  Wire.write(byte(0x00));     // set as 0
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x04));     // enter second MPOS address
  Wire.write(byte(0x00));     // set as 0
  Wire.endTransmission();
  delay(5);


  // set configuration settings  
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x07));       // enter first config address
  Wire.write(byte(0x03));    // switch off watchdog, switch off fast filtering, and turn slow filtering to fastest responce
//  IWire.write(byte(0x3F));    //
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0x08));    // enter second config address
  Wire.write(byte(0x20));   // switch off watchdog, switch off fast filtering, and turn slow filtering to fastest responce
//  Wire.write(byte(0xE3));   // switch off watchdog, switch off fast filtering, and turn slow filtering to fastest responce
  Wire.endTransmission();
  delay(5);
}

void AS5600_I2C_setup_2()
{
  I2Ctwo.begin(SDA_2, SCL_2, 400000);
  delay(5);

  // set start position (ZPOS) as 0 
  I2Ctwo.beginTransmission(byte(0x36));  
  I2Ctwo.write(byte(0x01));    // enter first ZPOS address
  I2Ctwo.write(byte(0x00));    // set as 0
  I2Ctwo.endTransmission();
  delay(5);
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x02));     // enter second ZPOS address
  I2Ctwo.write(byte(0x00));     // set as 0
  I2Ctwo.endTransmission();
  delay(5);

  // set stop position (MPOS) as 0 
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x03));     // enter second MPOS address
  I2Ctwo.write(byte(0x00));     // set as 0
  I2Ctwo.endTransmission();
  delay(5);
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x04));     // enter second MPOS address
  I2Ctwo.write(byte(0x00));     // set as 0
  I2Ctwo.endTransmission();
  delay(5);


  // set configuration settings  
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x07));       // enter first config address
  I2Ctwo.write(byte(0x03));    // switch off watchdog, switch off fast filtering, and turn slow filtering to fastest responce
//  II2Ctwo.write(byte(0x3F));    //
  I2Ctwo.endTransmission();
  delay(5);
  I2Ctwo.beginTransmission(byte(0x36));
  I2Ctwo.write(byte(0x08));    // enter second config address
  I2Ctwo.write(byte(0x20));   // switch off watchdog, switch off fast filtering, and turn slow filtering to fastest responce
//  I2Ctwo.write(byte(0xE3));   // switch off watchdog, switch off fast filtering, and turn slow filtering to fastest responce
  I2Ctwo.endTransmission();
  delay(5);
}

int AS5600_I2C_update_1()
{

  Wire.beginTransmission(byte(0x36));
//  Wire.write(byte(0X0C));  //raw angle
  Wire.write(byte(0X0E)); // filtered angle
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
//  I2Ctwo.write(byte(0X0C));  //raw angle
  I2Ctwo.write(byte(0X0E)); // filtered angle
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

void enc_motor_update()
{
  static double prevAngle[2] = {0, 0};
  static int multiplyAngle[2] = {0, 0};

  currAngle[0] = AS5600_I2C_update_1();
  currAngle[1] = AS5600_I2C_update_2();
  for (int i = 0; i < 2; i++)
  {
    //    0 = -180
    //    1024 = -90
    //    2048 = 0
    //    3072 = 90
    //    4096 = 180
    if ((prevAngle[i] >= 3072 && prevAngle[i]  <= 4096  ) && ( currAngle[i]  >=  0 &&  currAngle[i]  <= 1024 )  ) multiplyAngle[i]++;
    else if ((prevAngle[i]  >=  0 &&  prevAngle[i]  <= 1024 ) && (currAngle[i]  >= 3072 && currAngle[i]  <= 4096)  ) multiplyAngle[i]--;
    prevAngle[i]  = currAngle[i] ;

    currAngle[i]  = currAngle[i]  + multiplyAngle[i]  * 4096;
  }

}

// return distance made from the total encoder count
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
  return distance[returnNum];
}
