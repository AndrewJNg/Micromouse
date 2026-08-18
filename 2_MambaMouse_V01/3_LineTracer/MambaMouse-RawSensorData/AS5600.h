
#define SDA_1 21
#define SCL_1 22

#define SDA_2 18
#define SCL_2 19

//TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

int value;

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
  value = ( high << 8 ) | low;
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
  value = ( high << 8 ) | low;
  return value;
}
