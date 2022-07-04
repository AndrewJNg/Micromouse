// User Interface via potentiometers and OLED display, along with a battery management system
int pot_Value = 0;
const int pot_Pin = 36;
const byte battMonitor_Pin = 32;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//disable voltage_level reading for 6 sensor configuration



//const float R2 = 10.00;  // in kOhm
//const float R1 = 9.85 + 9.77;
//float voltage_level()
//{
//  float input_volt = (map(analogRead(battMonitor_Pin), 0, 4095, 0, 3300)) / 1000.00 ;
//  return (input_volt / (R2 / (R1 + R2)));
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long OLED_prevMillis = 0;

void OLED_display()
{
  unsigned long OLED_currentMillis = millis();

  // OLED display refresh at 20Hz
  if (OLED_currentMillis - OLED_prevMillis >= 50) {
    OLED_prevMillis = OLED_currentMillis;

    OLED.clearDisplay();

    OLED.setTextSize(1);      // Normal 1:1 pixel scale
    OLED.setTextColor(SSD1306_WHITE); // Draw white text
    OLED.setCursor(0, 0);     // Start at top-left corner
    //    OLED.print("Volt: ");
    //    OLED.println(Voltage_level());

    OLED.print("L_Enc: ");
    OLED.println(AS5600_I2C_update_1());
    //    OLED.println();
    OLED.print("R_Enc: ");
    OLED.println(AS5600_I2C_update_2());
    OLED.println();

    OLED.print("L_Motor: ");
    OLED.println(PS3_LeftAnalogStickSpeed(stick_LX, stick_LY));
    //    OLED.println();
    OLED.print("R_Motor: ");
    OLED.println(PS3_LeftAnalogStickSpeed(stick_RX, stick_RY));
    OLED.println();
//    OLED.print("IRFront:  ");
//    OLED.print(IRVal[0]);
//    OLED.print("  ");
//    OLED.println(IRVal[5]);
//
//    OLED.print("IR45:     ");
//    OLED.print(IRVal[1] );
//    OLED.print("  ");
//    OLED.println(IRVal[4] );
//
//    OLED.print("IRSide:   ");
//    OLED.print(IRVal[2]);
//    OLED.print("  ");
//    OLED.println(IRVal[3]);

    OLED.println("Gyro    ");
    OLED.print("X:");
    OLED.print( gyroX, 1);
    OLED.print(" Y:");
    OLED.print( gyroY, 1);
    OLED.print(" Z:");
    OLED.println( gyroZ, 1);




    OLED.display();
  }
}

void user_interface_setup()
{
  // User_interface setup
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    //    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  OLED.clearDisplay();
  OLED.display();

}
