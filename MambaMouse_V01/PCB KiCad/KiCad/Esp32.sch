EESchema Schematic File Version 4
LIBS:Micromouse_V01-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
L ESP32-footprints-Shem-Lib:ESP32-WROOM U?
U 1 1 621BA70A
P 4500 2550
AR Path="/621BA70A" Ref="U?"  Part="1" 
AR Path="/6211C239/621BA70A" Ref="U11"  Part="1" 
F 0 "U11" H 4475 3937 60  0000 C CNN
F 1 "ESP32-WROOM" H 4475 3831 60  0000 C CNN
F 2 "parts:MODULE_ESP32_DEVKIT_V1" H 4850 3900 60  0001 C CNN
F 3 "" H 4050 3000 60  0001 C CNN
	1    4500 2550
	1    0    0    -1  
$EndComp
Text GLabel 5600 1800 2    50   BiDi ~ 0
23
Text GLabel 5600 1900 2    50   BiDi ~ 0
22_SCL1
Text GLabel 5600 2000 2    50   BiDi ~ 0
1
Text GLabel 5600 2100 2    50   BiDi ~ 0
3
Text GLabel 5600 2200 2    50   BiDi ~ 0
21_SDA1
Text GLabel 5600 2400 2    50   BiDi ~ 0
19_SCL2
Text GLabel 5600 2500 2    50   BiDi ~ 0
18_SDA2
Text GLabel 5600 2600 2    50   BiDi ~ 0
5
Text GLabel 5600 2700 2    50   BiDi ~ 0
17
Text GLabel 5600 2800 2    50   BiDi ~ 0
16
Text GLabel 5600 2900 2    50   BiDi ~ 0
4
Text GLabel 4950 3750 3    50   BiDi ~ 0
2
Text GLabel 4850 3750 3    50   BiDi ~ 0
15
Text GLabel 4150 3750 3    50   BiDi ~ 0
13
Text GLabel 3400 3150 0    50   BiDi ~ 0
12
Text GLabel 3400 3050 0    50   BiDi ~ 0
14
Text GLabel 3400 2950 0    50   BiDi ~ 0
27
Text GLabel 3400 2850 0    50   BiDi ~ 0
26
Text GLabel 3400 2750 0    50   BiDi ~ 0
25
Text GLabel 3400 2650 0    50   BiDi ~ 0
33
Text GLabel 3400 2550 0    50   BiDi ~ 0
32
Text GLabel 3400 2450 0    50   BiDi ~ 0
35
Text GLabel 3400 2350 0    50   BiDi ~ 0
34
Text GLabel 3400 2250 0    50   BiDi ~ 0
39
Text GLabel 3400 2150 0    50   BiDi ~ 0
36
Wire Wire Line
	4150 3750 4150 3600
Wire Wire Line
	4950 3750 4950 3600
Wire Wire Line
	4850 3600 4850 3750
Wire Wire Line
	5600 2900 5400 2900
Wire Wire Line
	5400 2800 5600 2800
Wire Wire Line
	5600 2700 5400 2700
Wire Wire Line
	5400 2600 5600 2600
Wire Wire Line
	5600 2500 5400 2500
Wire Wire Line
	5400 2400 5600 2400
Wire Wire Line
	5600 2200 5400 2200
Wire Wire Line
	5400 2100 5600 2100
Wire Wire Line
	5600 2000 5400 2000
Wire Wire Line
	5400 1900 5600 1900
Wire Wire Line
	5600 1800 5400 1800
Wire Wire Line
	3550 2150 3400 2150
Wire Wire Line
	3400 2250 3550 2250
Wire Wire Line
	3550 2350 3400 2350
Wire Wire Line
	3400 2450 3550 2450
Wire Wire Line
	3550 2550 3400 2550
Wire Wire Line
	3400 2650 3550 2650
Wire Wire Line
	3550 2750 3400 2750
Wire Wire Line
	3550 2850 3400 2850
Wire Wire Line
	3400 2950 3550 2950
Wire Wire Line
	3550 3050 3400 3050
Wire Wire Line
	3400 3150 3550 3150
$Comp
L power:GND #PWR0145
U 1 1 62B80FB6
P 4050 4050
F 0 "#PWR0145" H 4050 3800 50  0001 C CNN
F 1 "GND" H 4055 3877 50  0000 C CNN
F 2 "" H 4050 4050 50  0001 C CNN
F 3 "" H 4050 4050 50  0001 C CNN
	1    4050 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 4050 4050 3600
Wire Wire Line
	3550 3250 3550 4050
Wire Wire Line
	3550 4050 4050 4050
Connection ~ 4050 4050
$Comp
L power:+3V3 #PWR0146
U 1 1 62B81A48
P 2800 1550
F 0 "#PWR0146" H 2800 1400 50  0001 C CNN
F 1 "+3V3" H 2815 1723 50  0000 C CNN
F 2 "" H 2800 1550 50  0001 C CNN
F 3 "" H 2800 1550 50  0001 C CNN
	1    2800 1550
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0147
U 1 1 62B82086
P 6650 2100
F 0 "#PWR0147" H 6650 1950 50  0001 C CNN
F 1 "VCC" H 6667 2273 50  0000 C CNN
F 2 "" H 6650 2100 50  0001 C CNN
F 3 "" H 6650 2100 50  0001 C CNN
	1    6650 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2100 6650 2300
Wire Wire Line
	6650 2300 5400 2300
NoConn ~ 3550 2050
NoConn ~ 4250 3600
NoConn ~ 4350 3600
NoConn ~ 4450 3600
NoConn ~ 4550 3600
NoConn ~ 4650 3600
NoConn ~ 4750 3600
NoConn ~ 5400 3200
NoConn ~ 5400 3100
NoConn ~ 5400 3000
NoConn ~ 3550 1950
NoConn ~ 2800 1550
$EndSCHEMATC
