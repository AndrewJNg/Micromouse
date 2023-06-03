// Allows control using a PS3 controller by using the github library by jvpernis
//https://github.com/jvpernis/esp32-ps3
#include <Ps3Controller.h>

int player = 0;
int battery = 0;

int stick_LX;
int stick_LY;
int stick_RX;
int stick_RY;
int PS3Batt;
int PS3Select;

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

 if ( Ps3.event.button_down.select ) Start = false;
 if ( Ps3.event.button_down.start ) Start = true;
 //        Serial.println("Started pressing the select button");
 if ( Ps3.event.button_down.up )
 {
   Mode++;
   Start = false;
 }
 if ( Ps3.event.button_down.down )
 {
   Mode--;
   Start = false;
 }
//  if ( Ps3.event.button_down.triangle )move_forward_cells();
//  if ( Ps3.event.button_down.cross )align_to_front_wall();

//  if ( Ps3.event.button_down.right );
//  if ( Ps3.event.button_down.left );

//  if ( Ps3.event.button_down.circle )turn(90);
//  if ( Ps3.event.button_down.square )turn(-90);

 //  if ( Ps3.event.button_down.triangle )turnKp = turnKp + 0.1;
 //  if ( Ps3.event.button_down.cross )turnKp = turnKp - 0.1;
 //
 //  if ( Ps3.event.button_down.right )turnKi = turnKi + 2;
 //  if ( Ps3.event.button_down.left )turnKi = turnKi - 2;
 //
 //  if ( Ps3.event.button_down.circle )turnKd = turnKd + 0.0001;
 //  if ( Ps3.event.button_down.square )turnKd = turnKd - 0.0001;
 /*
   if ( Ps3.event.button_down.triangle )straightKp = straightKp + 0.1;
   if ( Ps3.event.button_down.cross )straightKp = straightKp - 0.1;

   if ( Ps3.event.button_down.right )straightKi = straightKi + 0.1;
   if ( Ps3.event.button_down.left )straightKi = straightKi - 0.1;

   if ( Ps3.event.button_down.circle )straightKd = straightKd + 0.001;
   if ( Ps3.event.button_down.square )straightKd = straightKd - 0.001;
 */
      
  //  if ( Ps3.event.button_down.triangle )Junction(runSpeed, lineKp, lineKi, lineKd, 'M', 'I');
  //  if ( Ps3.event.button_down.cross )Junction(runSpeed, lineKp, lineKi, lineKd, 'M', 's');

  //  if ( Ps3.event.button_down.right )Junction(runSpeed, lineKp, lineKi, lineKd, 'R', 'R');
  //  if ( Ps3.event.button_down.left )Junction(runSpeed, lineKp, lineKi, lineKd, 'L', 'L');

  //  if ( Ps3.event.button_down.circle )lineKd = lineKd + 0.01;
  //  if ( Ps3.event.button_down.square )lineKd = lineKd - 0.01;

  //  if ( Ps3.event.button_down.r1 )runSpeed = runSpeed + 10;
  //  if ( Ps3.event.button_down.l1 )runSpeed = runSpeed - 10;
      
   if ( Ps3.event.button_down.triangle )lineKp = lineKp + 0.1;
   if ( Ps3.event.button_down.cross )lineKp = lineKp - 0.1;

   if ( Ps3.event.button_down.right )lineKi = lineKi + 0.001;
   if ( Ps3.event.button_down.left )lineKi = lineKi - 0.001;

   if ( Ps3.event.button_down.circle )lineKd = lineKd + 0.01;
   if ( Ps3.event.button_down.square )lineKd = lineKd - 0.01;

   if ( Ps3.event.button_down.r1 )runSpeed = runSpeed + 10;
   if ( Ps3.event.button_down.l1 )runSpeed = runSpeed - 10;
   
 //---------------------- Battery events ---------------------
 if ( battery != Ps3.data.status.battery ) {
   battery = Ps3.data.status.battery;
   //        Serial.print("The controller battery is ");
   if ( battery == ps3_status_battery_charging )      PS3Batt = 5;
   else if ( battery == ps3_status_battery_full )     PS3Batt = 4;
   else if ( battery == ps3_status_battery_high )     PS3Batt = 3;
   else if ( battery == ps3_status_battery_low)       PS3Batt = 2;
   else if ( battery == ps3_status_battery_dying )    PS3Batt = 1;
   else if ( battery == ps3_status_battery_shutdown ) PS3Batt = 0;
   //        else Serial.println("UNDEFINED");
 }
}

void onConnect() {
 //  Serial.println("Connected.");
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

float PS3_LeftAnalogStickSpeed(int X, int Y)
{
 float X_vector = 0;
 float Y_vector = 0;
 //  if (abs(LX) > 15) LX_vector = map(LX, -128, 127, -10000, 10000) / 100;
 if (abs(X) > 15) X_vector = map(X, -128, 127, -10000, 10000) / 100;
 //  else LX_vector = 0;
 //  if (abs(LY) > 15) LY_vector = map(LY, -127, 128, -10000, 10000) / 100;
 if (abs(Y) > 15) Y_vector = map(Y, -127, 128, -25500, 25500) / 100;
 //  else LY_vector = 0;

 //  float Speed = sqrt(LX_vector * LX_vector + LY_vector * LY_vector);
 float Speed = Y_vector;//sqrt( LY_vector);
 //  if (Speed > 100) Speed = 100;

 //  Serial.println(Speed);
 return Speed;
}

void PS3_setup()
{
 Ps3.attach(notify);
 Ps3.attachOnConnect(onConnect);
 Ps3.begin("bb:bb:bb:bb:bb:bb");

}
