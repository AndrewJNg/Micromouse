
int value;

void AS5600_I2C_setup()
{
  
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

int AS5600_I2C_update()
{
  
  Wire.beginTransmission(byte(0x36));
  Wire.write(byte(0X0C));
  Wire.endTransmission();
  Wire.requestFrom(byte(0x36), 2);
  while (Wire.available() < 2)
    ;

  int high = Wire.read();
  int low = Wire.read();
  value = ( high << 8 ) | low;
  return value;
}
