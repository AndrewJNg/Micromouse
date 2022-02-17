

class IR_sensor {
    int point_num;  //set number of reading samples
    long values[100];
    long sum;
    int average;
    byte IR_pin;
    double a;
    double b;
    byte emitter_pin;

  public:
    IR_sensor(byte emitter, byte pin, int points, int value1, int value2)
    { // setup for IR receivers
      IR_pin = pin;
      point_num = points;
      sum = 0;
      average = 0;
      a = value1;
      b = value2;
      emitter_pin = emitter;
//      pinMode(emitter_pin, OUTPUT);
    }

    double Distance()
    {
      //retrieve IR reading samples
//      digitalWrite(emitter_pin, HIGH);
      for ( int i = 0; i < point_num; i++ )
      {
        values[i] = 1023 - analogRead(IR_pin);
      }
//      digitalWrite(emitter_pin, LOW);

      // obtain average value
      sum = 0;
      for ( int i = 0; i < point_num; i++ )  {
        sum +=  values[ i ];
//  Serial.println(sum);
      }
      average = sum / point_num;

  Serial.print(average);
  Serial.print("    ");
      //convert readings to distance in mm
      //      Serial.print(average);
      //      Serial.print("    ");
      int y = average;
      double reading = a / (y - b);
      //reading = 1/reading;
      //      double output = 36.8701/(1.0312e3*((1/y)-(1/1.0312e3)));
      return reading ;
    }

};
