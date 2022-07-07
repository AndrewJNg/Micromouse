// User Interface via potentiometers and OLED display, along with a battery management system
int pot_Value = 0;
const int pot_Pin = 36;
const byte battMonitor_Pin = 32;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool left_IR_button();
bool right_IR_button();

class button
{
  public:
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    boolean lastButtonState = false;   // the previous reading from the input pin
    int buttonState = 0;           // the current reading from the input pin
    unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
    
//    int counter = 0;
    int count(bool  reading, int* subject  , int increment);
};

//  button function to allow debouncing of inputs and incrementing to a value
// expample, 
// (mode = subject=0, increment=1) 
// it will take the input value from a button (either 0 or 1), filter the result and return it by modying the passed in mode pointer  
int button::count(bool  reading , int* subject ,int increment)
{
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
       *subject = *subject + increment;
      }
    }
  }
  lastButtonState = reading;
  return *subject;
}


button IR_left_menu;
button IR_right_menu;



//disable voltage_level reading for 6 sensor configuration
//const float R2 = 10.00;  // in kOhm
//const float R1 = 9.85 + 9.77;
float voltage_level()
{
  //  float input_volt = (map(analogRead(battMonitor_Pin), 0, 4095, 0, 3300)) / 1000.00 ;
  //  return (input_volt / (R2 / (R1 + R2)));
  return map(PS3Batt, 0, 4, 0, 99);

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
