#include "Arduino.h"
#include "LDRLineSensor.h"

/*  
*   Constructor Parameters 
*   ( pins[rightMotorEnable, rightMotorDirF, rightMotorDirB,leftMotorEnable, leftMotorDirF, leftMotorDirB], rightDefaultSpeed, leftDefaultSpeed ) 
*   
*/    

LineSensor::LineSensor() {

}

LineSensor::LineSensor(int noOfSensors, int pins[], int ranges[][2]) {
        n_sensors = noOfSensors;
        middleSensorPin = pins[n_sensors/2];
        middleSensorRange[0] = ranges[n_sensors/2][0];
        middleSensorRange[1] = ranges[n_sensors/2][1];


        n_left = 0;
        // Add pins and ranges to right sensor array
        for(int i = 0;i < n_sensors/2; i++) {
            n_left += 1;
            leftSensors[i] = pins[i];
            leftSensorsRange[i][0] = ranges[i][0]; 
            leftSensorsRange[i][1] = ranges[i][1];
        }

        n_right = 0;
        // Add pins and ranges to left sensor array
        for(int i = n_sensors/2+1, j = 0;i < n_sensors; i++, j++) {
            n_right += 1;
            rightSensors[j] = pins[j];
            rightSensorsRange[j][0] = ranges[i][0];
            rightSensorsRange[j][1] = ranges[i][1];
        }

        // Enable all pins for Input
        for(int i = 0; i < n_sensors; i++) {
            pinMode(pins[i], INPUT);
        }

}


// int LineSensor::find()
//      Returns the current direction
// 
direction LineSensor::find() {

    int left = 0;
    for(int i = 0; i < n_left; i++) {
        int pinVal = analogRead(leftSensors[i]);
        int minVal = leftSensorsRange[i][0];
        int maxVal = leftSensorsRange[i][1];

        if(pinVal <= maxVal && pinVal >= minVal) {
            left += 1;
        }
    }

    int middle = 0;
    {
        int pinVal = analogRead(middleSensorPin);
        int minVal = middleSensorRange[0];
        int maxVal = middleSensorRange[1];

        if(pinVal <= maxVal && pinVal >= minVal) {
            middle += 1;
        }

    }

    int right = 0;
    for(int i = 0; i < n_right; i++) {
        int pinVal = analogRead(rightSensors[i]);
        int minVal = rightSensorsRange[i][0];
        int maxVal = rightSensorsRange[i][1];

        if(pinVal <= maxVal && pinVal >= minVal) {
            right += 1;
        }
    }

    // If left, right and middle all are 1
    // A white spot is there
    // direction = STOP
    // if( (left && middle && right) ) {
    //     sensed = STOP;
    // }
    // // If left, right and middle all are 0
    // // direction = dead end
    // else if( !(left && middle && right) ) {
    //     sensed = END;
    // }
    // // if only middle is 1
    // // direction = forward
    // else if( (!left && middle && !right) ) {
    //     sensed = FORWARD;
    // } 
    // // if left is 1 or left and middle borth are 1
    // // sensed = left
    // else if( (left && !middle && !right) || (left && middle && !right) ) {
    //     sensed = LEFT;
    // }
    // // if right is 1 or middle and right are 1
    // // sensed = right
    // else if( (!left && !middle && right) || (!left && middle && right) ) {
    //     sensed = RIGHT;
    // } 
    // else {
    //     sensed = UNKNOWN;   
    // }

    direction senses[] = {STOP, RIGHT, FORWARD, RIGHT, LEFT, UNKNOWN, LEFT, END};
    // Lookup Table
    // left middle right - integer - direction
    // 0    0       0       0           STOP
    // 0    0       1       1           RIGHT
    // 0    1       0       2           FORWARD
    // 0    1       1       3           RIGHT
    // 1    0       0       4           LEFT
    // 1    1       1       5           UNKNOWN
    // 1    0       0       6           LEFT
    // 1    1       1       7           END

    int bitmask = right | ( middle << 1) | (left << 2);
    return senses[bitmask];

}
