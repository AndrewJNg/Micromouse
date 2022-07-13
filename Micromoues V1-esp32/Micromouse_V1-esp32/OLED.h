// OLED display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long OledMillis = 0;
int OledInterval = 100;
static const unsigned char PROGMEM iQuick_logo[] =
{ //iQuick Logo

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x01, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x03, 0x80, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xc0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x0f, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xc0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x03, 0x80, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x01, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x06, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x0f, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x1f, 0x87, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x0f, 0xc7, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe7, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x03, 0xf3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x01, 0xf9, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0xfc, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x7e, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x3f, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0x9f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xcf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xe7, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xf3, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf9, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM battery_logo[] =
{ //Battery Logo
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3f, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0xc0, 0x00, 0x06, 0x00, 0xc0, 0x00, 0x07, 0x80,
  0xc0, 0x00, 0x07, 0x80, 0xc0, 0x00, 0x07, 0x80, 0xc0, 0x00, 0x07, 0x80, 0xc0, 0x00, 0x07, 0x80,
  0xc0, 0x00, 0x07, 0x80, 0xc0, 0x00, 0x07, 0x80, 0xc0, 0x00, 0x06, 0x00, 0x7f, 0xff, 0xfe, 0x00,
  0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM Calibrate_Logo[] =
{ // 'Calibrate', 106x30px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x03, 0xc3, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xfc, 0x00, 0x03, 0xc7, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1f, 0xfc, 0x00, 0x03, 0xc7, 0x87, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3f, 0xbc,
  0x00, 0x03, 0xc1, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x03,
  0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x78, 0x00, 0x06, 0x03, 0xc0, 0x07,
  0x08, 0x00, 0x10, 0x10, 0x07, 0x80, 0x10, 0x00, 0x78, 0x00, 0x3f, 0x83, 0xc7, 0x87, 0x3e, 0x0f,
  0x71, 0xfe, 0x1f, 0xe0, 0xfc, 0x00, 0x70, 0x00, 0x7f, 0xc3, 0xc7, 0x87, 0xff, 0x8f, 0xf1, 0xff,
  0x1f, 0xe1, 0xff, 0x00, 0xf0, 0x00, 0x41, 0xc3, 0xc7, 0x87, 0xcf, 0x8f, 0xf1, 0x07, 0x07, 0x83,
  0xc7, 0x00, 0xf0, 0x00, 0x00, 0xe3, 0xc7, 0x87, 0x87, 0x8f, 0x80, 0x07, 0x87, 0x03, 0x83, 0x80,
  0xf0, 0x00, 0x07, 0xe3, 0xc7, 0x87, 0x03, 0x8f, 0x00, 0x1f, 0x87, 0x07, 0x03, 0x80, 0xf0, 0x00,
  0x3f, 0xe3, 0xc7, 0x87, 0x03, 0x8f, 0x00, 0xff, 0x87, 0x07, 0xff, 0x80, 0x70, 0x00, 0x79, 0xe3,
  0xc7, 0x87, 0x03, 0x8f, 0x03, 0xe7, 0x87, 0x07, 0xff, 0x80, 0x78, 0x00, 0xe0, 0xe3, 0xc7, 0x87,
  0x03, 0x8f, 0x03, 0x87, 0x87, 0x07, 0x80, 0x00, 0x7c, 0x00, 0xe1, 0xe3, 0xc7, 0x87, 0x87, 0x8f,
  0x03, 0x87, 0x87, 0x87, 0x80, 0x00, 0x3f, 0xfc, 0xe1, 0xe3, 0xc7, 0x87, 0xcf, 0x8f, 0x03, 0x8f,
  0x87, 0x83, 0xc0, 0x00, 0x1f, 0xfc, 0xff, 0xe3, 0xc7, 0x87, 0xff, 0x0f, 0x03, 0xff, 0x87, 0xe1,
  0xff, 0x00, 0x0f, 0xfc, 0x7c, 0xe3, 0xc7, 0x87, 0xfe, 0x0f, 0x01, 0xf7, 0x83, 0xe0, 0xfe, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};


unsigned int getPosition = 0;
unsigned long OLED_prevMillis = 0;
void OLED_menu_display()
{



  if ((millis() > 3000) && (Start == LOW))
  {
    OLED.clearDisplay();


    //////////////////////////////////////////////////////////////////////////////////////////
    // battery
    OLED.drawBitmap(103, 0, battery_logo, 25, 20, 1);

    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(106, 7);
    OLED.cp437(true);
    OLED.print(int(voltage_level()));
    OLED.print("%");

    //////////////////////////////////////////////////////////////////////////////////////////

    OLED.fillRect(0, 0 , 20, 64, SSD1306_BLACK);

    OLED.drawRect(0, 0, 20, 16, SSD1306_WHITE);
    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(7, 4);
    OLED.cp437(true);
    OLED.write("4");

    OLED.drawRect(0, 15, 20, 16, SSD1306_WHITE);
    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(7, 19);
    OLED.cp437(true);
    OLED.write("3");

    OLED.drawRect(0, 31, 20, 16, SSD1306_WHITE);
    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(7, 35);
    OLED.cp437(true);
    OLED.write("2");

    OLED.drawRect(0, 47 , 20, 16, SSD1306_WHITE);
    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(7, 51);
    OLED.cp437(true);
    OLED.write("1");

    for (int x = 1; x < 5; x++)
    {
      int y = 64 - (x * 16);
      if (Mode == x)
      {
        OLED.fillRect(0, y , 20, 16, SSD1306_WHITE);
        OLED.setTextSize(1);
        OLED.setTextColor(SSD1306_BLACK);
        //        OLED.setCursor(7, y - 12);
        OLED.setCursor(7, y + 4);
        OLED.cp437(true);
        OLED.write(x + 48); // convert to ASCII number
      }
    }

    OLED.setTextColor(SSD1306_WHITE);
    OLED.cp437(true);
    if (Mode == 1)
    {
      OLED.setTextSize(7);
      OLED.setCursor(50, 10);
      OLED.print("1");
    }
    else if (Mode == 2)
    {
      OLED.setTextSize(7);
      OLED.setCursor(50, 10);
      OLED.print("2");
    }
    else if (Mode == 3)
    {
      OLED.drawBitmap(22, 35, Calibrate_Logo, 106, 30, 1);
    }
    else if (Mode == 4)
    {
      OLED.setTextSize(2);
      OLED.setCursor(30, 20);
      OLED.println("PS3");
      OLED.setCursor(30, 40);
      OLED.print("controls");
    }
  }
  OLED.display(); //update the display
}


void OledTimer()
{
  if (millis() - OledMillis >= OledInterval)
  {
    if ((Start == HIGH) && Mode != 4)
    {
      unsigned long RaceTime =  millis() - StartTimer ;
      unsigned long minutes = RaceTime / 60000;
      RaceTime -= minutes * 60000;
      unsigned long seconds = RaceTime / 1000;
      RaceTime -= seconds * 1000;
      unsigned long milliseconds = RaceTime;
      OLED.clearDisplay();
      if (minutes >= 100)
      {
        OLED.setTextSize(3);
        OLED.setTextColor(SSD1306_WHITE);
        OLED.setCursor(0, 0);
        OLED.cp437(true);
        OLED.print(minutes);
      }
      else  if (minutes >= 10)
      {
        OLED.setTextSize(4);
        OLED.setTextColor(SSD1306_WHITE);
        OLED.setCursor(0, 0);
        OLED.cp437(true);
        OLED.print(minutes);
      }
      else
      {
        OLED.setTextSize(4);
        OLED.setTextColor(SSD1306_WHITE);
        OLED.setCursor(23, 0);
        OLED.cp437(true);
        OLED.println(getPosition);
        OLED.print(minutes);
      }



      if (seconds >= 10)
      {
        OLED.print(":");
        OLED.println(seconds);
      }
      else
      {
        OLED.print(":0");
        OLED.println(seconds);
      }

      if (milliseconds >= 100)
      {
        OLED.setTextSize(3);
        OLED.setCursor(50, 40);
        OLED.print(":");
        OLED.print(milliseconds);
      }
      else if (milliseconds >= 10)
      {
        OLED.setTextSize(3);
        OLED.setCursor(50, 40);
        OLED.print(":0");
        OLED.print(milliseconds);
      }
      else if (milliseconds >= 1)
      {
        OLED.setTextSize(3);
        OLED.setCursor(50, 40);
        OLED.print(":00");
        OLED.print(milliseconds);
      }
      else
      {
        OLED.setTextSize(3);
        OLED.setCursor(50, 40);
        OLED.print(":000");
      }





      OLED.display(); //update the display
    }
    OledMillis = millis();
  }
}



void OLED_display_stats()
{
  static unsigned long prevMillis = 0;
  unsigned long currentMillis = millis();

  // OLED display refresh at 10Hz
  if (currentMillis - prevMillis >= 100) {
    prevMillis = currentMillis;
    unsigned long timeRecord = micros();

    OLED.clearDisplay();

    OLED.setTextSize(1);      // Normal 1:1 pixel scale
    OLED.setTextColor(SSD1306_WHITE); // Draw white text
    OLED.setCursor(0, 0);     // Start at top-left corner

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // motor & encoder

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // IR
    OLED.print("IRFront:  ");
    OLED.print(IRVal[0]);
    OLED.print("  ");
    OLED.println(IRVal[5]);

    OLED.print("IR45:     ");
    OLED.print(IRVal[1] );
    OLED.print("  ");
    OLED.println(IRVal[4] );

    OLED.print("IRSide:   ");
    OLED.print(IRVal[2]);
    OLED.print("  ");
    OLED.println(IRVal[3]);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Gyro
    //    OLED.println("Gyro    ");
//    OLED.println("  ");
//    OLED.print("X:");
//    OLED.print( gyroX, 1);
//    OLED.print(" Y:");
//    OLED.print( gyroY, 1);
//    OLED.print(" Z:");
//    //    OLED.println( gyroZ, 1);
//    OLED.println( MPU_Z_angle(), 1);

//    OLED.print("OLED: ");
//    OLED.println(micros() - timeRecord);
    
    OLED.print("P: ");
    OLED.println(turnKp,5);
    OLED.print("I: ");
    OLED.println(turnKi,5);
    OLED.print("D: ");
    OLED.println(turnKd,5);
    /*
     
    OLED.print("P: ");
    OLED.println(straightKp,5);
    OLED.print("I: ");
    OLED.println(straightKi,5);
    OLED.print("D: ");
    OLED.println(straightKd,5);
     */
//    OLED.print("P: ");
//    OLED.println(Kp);
//    OLED.print("I: ");
//    OLED.println(Ki);
//    OLED.print("D: ");
//    OLED.println(Kd);

//    OLED.print(" Set: ");
//    OLED.println( Setpoint);
//    OLED.print(" Z: ");
//    OLED.println( MPU_Z_angle(), 1);


    OLED.display();
  }
}


void OLED_setup()
{
  // User_interface setup
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    //    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  OLED.clearDisplay();
  OLED.display();

  //show logo
  OLED.clearDisplay();
  OLED.drawBitmap(  (OLED.width()  - 128 ) / 2, (OLED.height() - 64) / 2, iQuick_logo, 128, 64, 1);
  OLED.setTextSize(1);      // Normal 1:1 pixel scale
  OLED.setTextColor(SSD1306_WHITE); // Draw white text
  OLED.setCursor(45, 50);
  OLED.cp437(true);         // Use full 256 char 'Code Page 437' font
  OLED.print("iQuick");
  OLED.display();
}
