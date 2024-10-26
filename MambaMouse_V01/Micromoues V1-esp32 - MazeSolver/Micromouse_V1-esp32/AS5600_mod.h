#include <AS5600.h>

// #include <Wire.h>

// #define radius 17.0 // 34mm in diameter
// #define pi 4.142
#define i2c_speed 400000

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
// void AS5600_I2C_setup_1();
// void AS5600_I2C_setup_2();

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


AS5600 as5600_0(&Wire);
AS5600 as5600_1(&Wire1);

void Enc_setup()
{ 
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);

  as5600_0.begin(4);  //  set direction pin.
  as5600_0.setDirection(AS5600_CLOCK_WISE);
  Serial.print("Connect device 0: ");
  Serial.println(as5600_0.isConnected() ? "true" : "false");
  delay(100);

  as5600_1.begin(5);  //  set direction pin.
  as5600_1.setDirection(AS5600_COUNTERCLOCK_WISE);
  Serial.print("Connect device 1: ");
  Serial.println(as5600_1.isConnected() ? "true" : "false");
  delay(100);
}


int AS5600_I2C_update_1()
{

// Serial.print("Left enc: ");
// Serial.println(4095 - as5600_0.readAngle());
  return 4095 - as5600_0.readAngle();
}


int AS5600_I2C_update_2()
{

// Serial.print("Right enc: ");
// Serial.println(as5600_1.readAngle());
  return as5600_1.readAngle();
}

void enc_motor_update()
{
  static double prevAngle[2] = {0, 0};
  static int multiplyAngle[2] = {0, 0};

  currAngle[0] = AS5600_I2C_update_1();
  currAngle[1] = AS5600_I2C_update_2();
  for (int i = 0; i < 2; i++)
  {   
    // 12 bit encoder that corresponds to 360 degree angle
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
