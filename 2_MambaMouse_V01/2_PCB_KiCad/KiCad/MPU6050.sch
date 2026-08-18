EESchema Schematic File Version 4
LIBS:Micromouse_V01-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Sensor_Motion:MPU-6050 U?
U 1 1 62A8BF1F
P 5450 3550
AR Path="/62A8BF1F" Ref="U?"  Part="1" 
AR Path="/62A8A986/62A8BF1F" Ref="U13"  Part="1" 
F 0 "U13" H 5450 2764 50  0000 C CNN
F 1 "MPU-6050" H 5450 2673 50  0000 C CNN
F 2 "parts:MPU6050 module" H 5450 2750 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf" H 5450 3400 50  0001 C CNN
	1    5450 3550
	1    0    0    -1  
$EndComp
Text GLabel 6300 3250 2    50   BiDi ~ 0
23
Wire Wire Line
	6300 3250 6150 3250
$Comp
L power:GND #PWR?
U 1 1 62A8BF28
P 5450 4600
AR Path="/62A8BF28" Ref="#PWR?"  Part="1" 
AR Path="/62A8A986/62A8BF28" Ref="#PWR0148"  Part="1" 
F 0 "#PWR0148" H 5450 4350 50  0001 C CNN
F 1 "GND" H 5455 4427 50  0000 C CNN
F 2 "" H 5450 4600 50  0001 C CNN
F 3 "" H 5450 4600 50  0001 C CNN
	1    5450 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 4600 5450 4250
$Comp
L power:+3.3V #PWR?
U 1 1 62A8BF2F
P 5550 2700
AR Path="/62A8BF2F" Ref="#PWR?"  Part="1" 
AR Path="/62A8A986/62A8BF2F" Ref="#PWR0149"  Part="1" 
F 0 "#PWR0149" H 5550 2550 50  0001 C CNN
F 1 "+3.3V" H 5565 2873 50  0000 C CNN
F 2 "" H 5550 2700 50  0001 C CNN
F 3 "" H 5550 2700 50  0001 C CNN
	1    5550 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2700 5550 2850
Wire Wire Line
	4600 3250 4750 3250
Wire Wire Line
	4750 3350 4600 3350
NoConn ~ 6150 3450
NoConn ~ 6150 3550
NoConn ~ 6150 3750
NoConn ~ 6150 3850
NoConn ~ 4750 3850
NoConn ~ 4750 3750
NoConn ~ 4750 3450
NoConn ~ 5350 2850
Text GLabel 4600 3250 0    50   BiDi ~ 0
21_SDA1
Text GLabel 4600 3350 0    50   BiDi ~ 0
22_SCL1
$EndSCHEMATC
