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

const float R2 = 10.00;  // in kOhm
const float R1 = 9.85 + 9.77;

float Voltage_level()
{
  float input_volt = (map(analogRead(battMonitor_Pin), 0, 4095, 0, 3300)) / 1000.00 ;
  return (input_volt / (R2 / (R1 + R2)));
}



int IRFrontL = 0;
int IR45L = 0;
int IRSideL= 0;

int IRFrontR = 0;
int IR45R= 0;
int IRSideR= 0;
unsigned long OLED_prevMillis = 0;

void OLED_display()
{
  unsigned long OLED_currentMillis = millis();
  if (OLED_currentMillis - OLED_prevMillis >= 50) {

    OLED.clearDisplay();

    OLED.setTextSize(1);      // Normal 1:1 pixel scale
    OLED.setTextColor(SSD1306_WHITE); // Draw white text
    OLED.setCursor(0, 0);     // Start at top-left corner
//    OLED.print("Volt: ");
//    OLED.println(Voltage_level());

    OLED.print("L_Enc: ");
    OLED.println(4095-AS5600_I2C_update_1());
//    OLED.println();
    OLED.print("R_Enc: ");
    OLED.println(AS5600_I2C_update_2());
    OLED.println();
    
    OLED.print("IRFront:  ");
    OLED.print(IRFrontL);
    OLED.print("  ");
    OLED.println(IRFrontR);
    
    OLED.print("IR45:     ");
    OLED.print(IR45L );
    OLED.print("  ");
    OLED.println(IR45R );
    
    OLED.print("IRSide:   ");
    OLED.print(IRSideL);
    OLED.print("  ");
    OLED.println(IRSideR);

    OLED.println("Gyro    ");
    OLED.print("X:");
    OLED.print( gyroX,1);
    OLED.print(" Y:");
    OLED.print( gyroY,1);
    OLED.print(" Z:");
    OLED.println( gyroZ,1);
    

//    battery = Ps3.data.status.battery;
//    OLED.print("PS3:  ");
//    if ( battery == ps3_status_battery_charging )      OLED.print("charging");
//    else if ( battery == ps3_status_battery_full )     OLED.print("FULL");
//    else if ( battery == ps3_status_battery_high )     OLED.print("HIGH");
//    else if ( battery == ps3_status_battery_low)       OLED.print("LOW");
//    else if ( battery == ps3_status_battery_dying )    OLED.print("DYING");
//    else if ( battery == ps3_status_battery_shutdown ) OLED.print("SHUTDOWN");
//    else OLED.print("UNDEFINED");


    OLED.display();
    OLED_prevMillis = OLED_currentMillis;
  }

}
void User_interface_setup()
{
  
  // User_interface setup
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
//    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  OLED.clearDisplay();
  OLED.display();

}
