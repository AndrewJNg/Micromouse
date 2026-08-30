#include <Wire.h>
#include "MT6701.h"

// Left encoder I2C pins
#define SDA_1 21
#define SCL_1 22

// Right encoder I2C pins
#define SDA_2 18
#define SCL_2 19

// System speed
#define i2c_speed 400000

#define wheelRadius 17.0
MT6701 encoder;
MT6701 encoderRight;

#define PWMResolution 12
#define PWMResolutionMaxValue 4095

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_1, SCL_1, i2c_speed);
  Wire1.begin(SDA_2, SCL_2, i2c_speed);
  encoder.initializeI2C(&Wire, MT6701_DEFAULT_ADDRESS);
  encoderRight.initializeI2C(&Wire1, MT6701_DEFAULT_ADDRESS);

  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  ledcAttach(5, 5000, PWMResolution);

  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  ledcWrite(5, 0000);


  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  ledcAttach(15, 5000, PWMResolution);
  
  digitalWrite(4, LOW);
  digitalWrite(2, HIGH);
  ledcWrite(15, 0000);
}
int encoder_rot_count = 0;
float prev_angle = 0;
double prev_cumm_angle = 0;

void loop() {
  float angle = encoder.angleRead();
  if (prev_angle >= 270 & angle <= 90) encoder_rot_count++;
  if (prev_angle <= 90 & angle >= 270) encoder_rot_count--;

  Serial.print(millis());
  Serial.print("  ");
  Serial.print(angle);
  Serial.print("  ");
  Serial.print(encoderRight.angleRead());
  // Serial.print("  ");
  // Serial.print(prev_angle);
  // Serial.print("  ");
  // Serial.print(encoder_rot_count);
  // Serial.print("  ");

  prev_angle = angle;
  double cumm_angle = angle + encoder_rot_count * 360.0;

  double speed = cumm_angle - prev_cumm_angle;
  // Serial.print(cumm_angle);
  // Serial.print("  ");
  // Serial.print(prev_cumm_angle);
  // Serial.print("  ");
  prev_cumm_angle = cumm_angle;


  if (abs(speed) < 1.0) speed = 0;

  double speed_mm_per_second = (2 * M_PI * wheelRadius * (double)speed) / (360.00 * 0.005);
  // Serial.print(speed);
  // Serial.print("  ");
  // Serial.print(speed_mm_per_second);
  
  Serial.print("  ");
  Serial.println();
  delay(5);
}