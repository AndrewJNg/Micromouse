// Allows control using a PS3 controller by using the github library by jvpernis
//https://github.com/jvpernis/esp32-ps3
#include <Ps3Controller.h>

int player = 0;
int battery = 0;

int stick_LX;
int stick_LY;
int stick_RX;
int stick_RY;

int up_button;

void notify()
{
  if ( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ) {
    stick_LX = Ps3.data.analog.stick.lx;
    stick_LY = -Ps3.data.analog.stick.ly;
  }


  if ( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ) {
    stick_RX = Ps3.data.analog.stick.rx;
    stick_RY = -Ps3.data.analog.stick.ry;
  }


//    if( Ps3.event.button_down.up )
//        var =1;
//    if( Ps3.event.button_up.up )
//        var=0;
//  if(1)
//  {
//    
//Stepper_run(0);
//  }

  /*
    Serial.print(stick_LX); Serial.print("    ");
    Serial.print(stick_LY); Serial.print("    ");
    Serial.print(stick_RX); Serial.print("    ");
    Serial.print(stick_RY); Serial.print("    ");
    Serial.print(Ps3.data.button.l1); Serial.print("    ");
    Serial.println(Ps3.data.button.r1); Serial.print("    ");
  */
}

void onConnect() {
  Serial.println("Connected.");
}

float PS3_LeftAnalogStickAngle (int LX, int LY)
{
  float LX_vector = map(LX, -128, 127, -10000, 10000) / 100;
  float LY_vector = map(LY, -127, 128, -10000, 10000) / 100;
  float angle ;
  if (LY_vector == 0 && LX_vector > 0) angle = PI / 2;
  else if (LY_vector == 0 && LX_vector < 0) angle = 3 * PI / 2;
  else if (LY_vector == 0 && LX_vector == 0) angle = 0;
  else angle = atan(abs(LX_vector) / abs(LY_vector));
  //  angle = atan(abs(LX_vector) / abs(LY_vector));

  if ( LX_vector > 0 && LY_vector > 0) angle = angle;
  else if ( LX_vector > 0 && LY_vector < 0) angle = PI - angle ;
  else if ( LX_vector < 0 && LY_vector < 0) angle = PI + angle;
  else if ( LX_vector < 0 && LY_vector > 0) angle = 2 * PI - angle;

  //  Serial.println(angle * 180 / PI);
  return angle;
}

float PS3_LeftAnalogStickSpeed(int LX, int LY)
{
  float LX_vector = 0;
  float LY_vector = 0;
//  if (abs(LX) > 15) LX_vector = map(LX, -128, 127, -10000, 10000) / 100;
  if (abs(LX) > 15) LX_vector = map(LX, -128, 127, -10000, 10000) / 100;
//  else LX_vector = 0;
//  if (abs(LY) > 15) LY_vector = map(LY, -127, 128, -10000, 10000) / 100;
  if (abs(LY) > 15) LY_vector = map(LY, -127, 128, -25500, 25500) / 100;
//  else LY_vector = 0;

//  float Speed = sqrt(LX_vector * LX_vector + LY_vector * LY_vector);
  float Speed = LY_vector;//sqrt( LY_vector);
//  if (Speed > 100) Speed = 100;

  //  Serial.println(Speed);
  return Speed;
}

void PS3_setup()
{
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("01:02:03:04:05:06");
}
