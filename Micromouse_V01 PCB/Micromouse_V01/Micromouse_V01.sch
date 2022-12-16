EESchema Schematic File Version 4
LIBS:Micromouse_V01-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
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
L power:GND #PWR05
U 1 1 5D7B9B89
P 8750 5500
F 0 "#PWR05" H 8750 5250 50  0001 C CNN
F 1 "GND" H 8755 5327 50  0000 C CNN
F 2 "" H 8750 5500 50  0001 C CNN
F 3 "" H 8750 5500 50  0001 C CNN
	1    8750 5500
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR03
U 1 1 5D7BA56A
P 8350 5200
F 0 "#PWR03" H 8350 5050 50  0001 C CNN
F 1 "VCC" H 8367 5373 50  0000 C CNN
F 2 "" H 8350 5200 50  0001 C CNN
F 3 "" H 8350 5200 50  0001 C CNN
	1    8350 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 5200 8350 5200
$Comp
L Device:C C1
U 1 1 5D7BC19C
P 9100 5350
F 0 "C1" H 9215 5396 50  0000 L CNN
F 1 "100nF" H 9215 5305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9138 5200 50  0001 C CNN
F 3 "~" H 9100 5350 50  0001 C CNN
	1    9100 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D7BCB62
P 9450 5350
F 0 "C2" H 9565 5396 50  0000 L CNN
F 1 "100nF" H 9565 5305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9488 5200 50  0001 C CNN
F 3 "~" H 9450 5350 50  0001 C CNN
	1    9450 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 5500 9100 5500
Connection ~ 9100 5500
Wire Wire Line
	9100 5500 8750 5500
Wire Wire Line
	9050 5200 9100 5200
Connection ~ 9100 5200
$Comp
L power:VCC #PWR01
U 1 1 5E43674C
P 9950 4550
F 0 "#PWR01" H 9950 4400 50  0001 C CNN
F 1 "VCC" H 9967 4723 50  0000 C CNN
F 2 "" H 9950 4550 50  0001 C CNN
F 3 "" H 9950 4550 50  0001 C CNN
	1    9950 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPDT_x2 SW1
U 1 1 5E4470A8
P 9500 4450
F 0 "SW1" H 9500 4735 50  0000 C CNN
F 1 "SW_DPDT_x2" H 9500 4644 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPDT_PCM12" H 9500 4450 50  0001 C CNN
F 3 "" H 9500 4450 50  0001 C CNN
	1    9500 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 4550 9700 4550
NoConn ~ 9700 4350
$Comp
L Switch:SW_Push SW2
U 1 1 5E463AA7
P 4000 2650
F 0 "SW2" H 4000 2935 50  0000 C CNN
F 1 "Start" H 4000 2844 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 4000 2850 50  0001 C CNN
F 3 "" H 4000 2850 50  0001 C CNN
	1    4000 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 5E4806A5
P 4000 3350
F 0 "R18" V 3793 3350 50  0000 C CNN
F 1 "10K" V 3884 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3930 3350 50  0001 C CNN
F 3 "~" H 4000 3350 50  0001 C CNN
	1    4000 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 3200 4000 2850
$Comp
L power:GND #PWR07
U 1 1 5E4864AA
P 4000 3700
F 0 "#PWR07" H 4000 3450 50  0001 C CNN
F 1 "GND" H 4005 3527 50  0000 C CNN
F 2 "" H 4000 3700 50  0001 C CNN
F 3 "" H 4000 3700 50  0001 C CNN
	1    4000 3700
	1    0    0    -1  
$EndComp
Text GLabel 4000 3000 0    50   BiDi ~ 0
13
Text GLabel 2350 850  1    50   BiDi ~ 0
12
$Comp
L Device:Buzzer BZ1
U 1 1 5E431605
P 2600 1450
F 0 "BZ1" H 2753 1479 50  0000 L CNN
F 1 "Buzzer" H 2753 1388 50  0000 L CNN
F 2 "parts:4.2mm_5.5mm buzzer" V 2575 1550 50  0001 C CNN
F 3 "~" V 2575 1550 50  0001 C CNN
	1    2600 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E435CB4
P 2350 1600
F 0 "#PWR0101" H 2350 1350 50  0001 C CNN
F 1 "GND" H 2355 1427 50  0000 C CNN
F 2 "" H 2350 1600 50  0001 C CNN
F 3 "" H 2350 1600 50  0001 C CNN
	1    2350 1600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J3
U 1 1 6210FF12
P 2600 3700
F 0 "J3" H 2627 3676 50  0000 L CNN
F 1 "OLED" H 2627 3585 50  0000 L CNN
F 2 "parts:OLED 128x32" H 2600 3700 50  0001 C CNN
F 3 "~" H 2600 3700 50  0001 C CNN
	1    2600 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0104
U 1 1 6211009D
P 1650 3600
F 0 "#PWR0104" H 1650 3450 50  0001 C CNN
F 1 "+3V3" H 1665 3773 50  0000 C CNN
F 2 "" H 1650 3600 50  0001 C CNN
F 3 "" H 1650 3600 50  0001 C CNN
	1    1650 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 6211010C
P 1650 3700
F 0 "#PWR0105" H 1650 3450 50  0001 C CNN
F 1 "GND" H 1655 3527 50  0000 C CNN
F 2 "" H 1650 3700 50  0001 C CNN
F 3 "" H 1650 3700 50  0001 C CNN
	1    1650 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3700 1650 3700
Wire Wire Line
	2400 3600 1650 3600
$Sheet
S 600  600  1150 800 
U 6211C239
F0 "Esp32" 50
F1 "Esp32.sch" 50
$EndSheet
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 6211E4CA
P 8750 5200
F 0 "U1" H 8750 5442 50  0000 C CNN
F 1 "AMS1117-3.3" H 8750 5351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 8750 5400 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 8850 4950 50  0001 C CNN
	1    8750 5200
	1    0    0    -1  
$EndComp
Connection ~ 8750 5500
$Comp
L power:+3V3 #PWR0102
U 1 1 621217A0
P 9450 5200
F 0 "#PWR0102" H 9450 5050 50  0001 C CNN
F 1 "+3V3" H 9465 5373 50  0000 C CNN
F 2 "" H 9450 5200 50  0001 C CNN
F 3 "" H 9450 5200 50  0001 C CNN
	1    9450 5200
	1    0    0    -1  
$EndComp
Connection ~ 9450 5200
Wire Wire Line
	9100 5200 9450 5200
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 62123EB1
P 7500 4300
F 0 "J1" H 7527 4276 50  0000 L CNN
F 1 "Conn_01x02_Female" H 7527 4185 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 7500 4300 50  0001 C CNN
F 3 "~" H 7500 4300 50  0001 C CNN
	1    7500 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4300 7300 4300
$Comp
L power:GND #PWR0106
U 1 1 62125248
P 7000 4400
F 0 "#PWR0106" H 7000 4150 50  0001 C CNN
F 1 "GND" H 7005 4227 50  0000 C CNN
F 2 "" H 7000 4400 50  0001 C CNN
F 3 "" H 7000 4400 50  0001 C CNN
	1    7000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4400 7300 4400
$Comp
L Connector:Conn_01x04_Female J6
U 1 1 621E26D3
P 2550 2950
F 0 "J6" H 2577 2926 50  0000 L CNN
F 1 "AS5600 Right" H 2577 2835 50  0000 L CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x04_P2.00mm_Vertical" H 2550 2950 50  0001 C CNN
F 3 "~" H 2550 2950 50  0001 C CNN
	1    2550 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J5
U 1 1 621E278B
P 2550 2250
F 0 "J5" H 2577 2226 50  0000 L CNN
F 1 "AS5600 Left" H 2577 2135 50  0000 L CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x04_P2.00mm_Vertical" H 2550 2250 50  0001 C CNN
F 3 "~" H 2550 2250 50  0001 C CNN
	1    2550 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R19
U 1 1 62AC153C
P 2350 1200
F 0 "R19" H 2420 1246 50  0000 L CNN
F 1 "100" H 2420 1155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2280 1200 50  0001 C CNN
F 3 "~" H 2350 1200 50  0001 C CNN
	1    2350 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1350 2350 1350
Wire Wire Line
	2350 1600 2350 1550
Wire Wire Line
	2350 1550 2500 1550
Wire Wire Line
	2350 850  2350 1050
$Comp
L power:+BATT #PWR0103
U 1 1 62AE27E3
P 7000 4300
F 0 "#PWR0103" H 7000 4150 50  0001 C CNN
F 1 "+BATT" H 7015 4473 50  0000 C CNN
F 2 "" H 7000 4300 50  0001 C CNN
F 3 "" H 7000 4300 50  0001 C CNN
	1    7000 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0114
U 1 1 62AE47E3
P 9050 4450
F 0 "#PWR0114" H 9050 4300 50  0001 C CNN
F 1 "+BATT" H 9065 4623 50  0000 C CNN
F 2 "" H 9050 4450 50  0001 C CNN
F 3 "" H 9050 4450 50  0001 C CNN
	1    9050 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4450 9300 4450
$Sheet
S 950  4900 1500 1250
U 62AEF46B
F0 "IRsensor" 50
F1 "IRsensor.sch" 50
$EndSheet
Text GLabel 2150 3800 0    50   BiDi ~ 0
22_SCL1
Text GLabel 2150 3900 0    50   BiDi ~ 0
21_SDA1
Wire Wire Line
	2150 3800 2400 3800
Wire Wire Line
	2150 3900 2400 3900
$Comp
L power:+3V3 #PWR0138
U 1 1 62B4C2C3
P 1200 2250
F 0 "#PWR0138" H 1200 2100 50  0001 C CNN
F 1 "+3V3" H 1215 2423 50  0000 C CNN
F 2 "" H 1200 2250 50  0001 C CNN
F 3 "" H 1200 2250 50  0001 C CNN
	1    1200 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0139
U 1 1 62B4C2C9
P 1900 2150
F 0 "#PWR0139" H 1900 1900 50  0001 C CNN
F 1 "GND" H 1905 1977 50  0000 C CNN
F 2 "" H 1900 2150 50  0001 C CNN
F 3 "" H 1900 2150 50  0001 C CNN
	1    1900 2150
	1    0    0    -1  
$EndComp
Text GLabel 1800 2450 0    50   BiDi ~ 0
22_SCL1
Text GLabel 1800 2350 0    50   BiDi ~ 0
21_SDA1
Wire Wire Line
	1200 2250 2350 2250
Wire Wire Line
	1900 2150 2350 2150
Wire Wire Line
	1800 2350 2350 2350
Wire Wire Line
	2350 2450 1800 2450
Text GLabel 1800 3050 0    50   BiDi ~ 0
18_SDA2
Text GLabel 1800 3150 0    50   BiDi ~ 0
19_SCL2
$Comp
L power:+3V3 #PWR0140
U 1 1 62B53282
P 1200 2950
F 0 "#PWR0140" H 1200 2800 50  0001 C CNN
F 1 "+3V3" H 1215 3123 50  0000 C CNN
F 2 "" H 1200 2950 50  0001 C CNN
F 3 "" H 1200 2950 50  0001 C CNN
	1    1200 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0141
U 1 1 62B53288
P 1900 2850
F 0 "#PWR0141" H 1900 2600 50  0001 C CNN
F 1 "GND" H 1905 2677 50  0000 C CNN
F 2 "" H 1900 2850 50  0001 C CNN
F 3 "" H 1900 2850 50  0001 C CNN
	1    1900 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2950 2350 2950
Wire Wire Line
	1900 2850 2350 2850
Wire Wire Line
	1800 3050 2350 3050
Wire Wire Line
	2350 3150 1800 3150
Wire Wire Line
	4000 2250 4000 2450
Wire Wire Line
	4000 3700 4000 3500
$Comp
L Connector:Conn_01x02_Female J7
U 1 1 62A6C4F8
P 7500 5100
F 0 "J7" H 7527 5076 50  0000 L CNN
F 1 "Conn_01x02_Female" H 7527 4985 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 7500 5100 50  0001 C CNN
F 3 "~" H 7500 5100 50  0001 C CNN
	1    7500 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5100 7300 5100
$Comp
L power:GND #PWR0150
U 1 1 62A6C500
P 7000 5200
F 0 "#PWR0150" H 7000 4950 50  0001 C CNN
F 1 "GND" H 7005 5027 50  0000 C CNN
F 2 "" H 7000 5200 50  0001 C CNN
F 3 "" H 7000 5200 50  0001 C CNN
	1    7000 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5200 7300 5200
$Comp
L power:+BATT #PWR0151
U 1 1 62A6C507
P 7000 5100
F 0 "#PWR0151" H 7000 4950 50  0001 C CNN
F 1 "+BATT" H 7015 5273 50  0000 C CNN
F 2 "" H 7000 5100 50  0001 C CNN
F 3 "" H 7000 5100 50  0001 C CNN
	1    7000 5100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J8
U 1 1 62A6DA1D
P 7500 5700
F 0 "J8" H 7527 5676 50  0000 L CNN
F 1 "Conn_01x02_Female" H 7527 5585 50  0000 L CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x02_P2.00mm_Vertical" H 7500 5700 50  0001 C CNN
F 3 "~" H 7500 5700 50  0001 C CNN
	1    7500 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5700 7300 5700
$Comp
L power:GND #PWR0152
U 1 1 62A6DA25
P 7000 5800
F 0 "#PWR0152" H 7000 5550 50  0001 C CNN
F 1 "GND" H 7005 5627 50  0000 C CNN
F 2 "" H 7000 5800 50  0001 C CNN
F 3 "" H 7000 5800 50  0001 C CNN
	1    7000 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5800 7300 5800
$Comp
L power:+BATT #PWR0153
U 1 1 62A6DA2C
P 7000 5700
F 0 "#PWR0153" H 7000 5550 50  0001 C CNN
F 1 "+BATT" H 7015 5873 50  0000 C CNN
F 2 "" H 7000 5700 50  0001 C CNN
F 3 "" H 7000 5700 50  0001 C CNN
	1    7000 5700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 62AE8436
P 4550 2650
F 0 "SW3" H 4550 2935 50  0000 C CNN
F 1 "Start" H 4550 2844 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 4550 2850 50  0001 C CNN
F 3 "" H 4550 2850 50  0001 C CNN
	1    4550 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 2450 4000 2450
Connection ~ 4000 2450
Wire Wire Line
	4550 2850 4000 2850
Connection ~ 4000 2850
$Comp
L power:+3.3V #PWR0154
U 1 1 62B1C577
P 4000 2250
F 0 "#PWR0154" H 4000 2100 50  0001 C CNN
F 1 "+3.3V" H 4015 2423 50  0000 C CNN
F 2 "" H 4000 2250 50  0001 C CNN
F 3 "" H 4000 2250 50  0001 C CNN
	1    4000 2250
	1    0    0    -1  
$EndComp
$Sheet
S 5950 1200 1100 850 
U 62A8654D
F0 "TB6612FNG" 50
F1 "TB6612FNG.sch" 50
$EndSheet
$Sheet
S 8250 1300 1050 1000
U 62A8A986
F0 "MPU6050" 50
F1 "MPU6050.sch" 50
$EndSheet
$EndSCHEMATC
