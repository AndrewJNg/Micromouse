// User Interface via potentiometers and OLED display, along with a battery management system
int pot_Value = 0;
const int pot_Pin = 36;
const byte battMonitor_Pin = 32;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool left_IR_button();
bool right_IR_button();


//disable voltage_level reading for 6 sensor configuration
//const float R2 = 10.00;  // in kOhm
//const float R1 = 9.85 + 9.77;
float voltage_level()
{
//  float input_volt = (map(analogRead(battMonitor_Pin), 0, 4095, 0, 3300)) / 1000.00 ;
//  return (input_volt / (R2 / (R1 + R2)));
 return map(PS3Batt,0,4,0,99);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool left_IR_button()
{
  int sum = 0;
  for (int i = 0; i < 3; i++)
  {
    if (IRVal[i] > 3000) sum++;

  }
  //  Serial.print(sum);
  //  Serial.print("  ");
  if (sum == 3)return true;
  else return false;
}

bool right_IR_button()
{
  int sum = 0;
  for (int i = 3; i < 6; i++)
  {
    if (IRVal[i] > 3000) sum++;

  }
  //  Serial.print(sum);
  //  Serial.print("  ");
  if (sum == 3)return true;
  else return false;
}


int counter = 0;
int count_minus()
{
  //  static int counter=0;
  static unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  static unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
  static boolean lastButtonState = false;   // the previous reading from the input pin
  static int buttonState = 0;           // the current reading from the input pin

  int reading = left_IR_button();


  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //        counter--;
        Mode--;

        Start = false;
      }

    }
  }

  // set the LED:

  lastButtonState = reading;
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  return counter;
}

int count_plus()
{
  static unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  static unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
  static boolean lastButtonState = false;   // the previous reading from the input pin
  static int buttonState = 0;           // the current reading from the input pin

  int reading = right_IR_button();


  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        //        counter++;
        //        Mode++;
        //        if (Mode > 4)
        //        {
        //          Mode = 1;
        //        }
        //        else if (Mode < 1)
        //        {
        //          Mode = 4;
        //        }
        Start = true;
      }

    }
  }

  // set the LED:

  lastButtonState = reading;
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  return counter;
}
