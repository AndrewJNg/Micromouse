#ifndef LDRLineSensor_h
#define LDRLineSensor_h

#include "Arduino.h"
enum direction {
    FORWARD,
    BACKWARD,
    STOP,
    LEFT,
    RIGHT,
    END,
    UNKNOWN
};  

class LineSensor  {
  
private :
    int n_sensors;         
    // No Of Sensors Attached; Preferably Odd; 1-Indexed
    
    int sensor_pins[];     
    // The pins to which the sensors are connected as an array
    // from left to right respectively.
    int sensors_range[][2];
    // Analog range's for all the respective sensors
    // Each index contains an array containing { minValue, maxValue}

    int middleSensorPin;   
    // Pin for the middle sensor
    int middleSensorRange[2];
    // Range array for the middle sensor

    int n_left;
    // No Of Sensors on the left
    int leftSensors[]; 
    // Pins for the sensors on left side
    int leftSensorsRange[][2];
    // Ranges for the left sensors

    int n_right;
    // No Of Sensors on the right
    int rightSensors[];
    // Pins For The Sensors on the right side
    int rightSensorsRange[][2];
    // Ranges for the right sensors
public:
    LineSensor();
    LineSensor(int, int[], int[][2]);
    direction find();
};

#endif
