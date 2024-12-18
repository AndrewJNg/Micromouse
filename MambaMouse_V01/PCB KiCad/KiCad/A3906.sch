EESchema Schematic File Version 4
LIBS:Micromouse_V01-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L A3906:A3906 U5
U 1 1 5DFD57AB
P 2700 2900
F 0 "U5" H 2700 1964 50  0000 C CNN
F 1 "A3906" H 2700 1873 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.5x2.5mm_ThermalVias" H 2700 3600 50  0001 C CNN
F 3 "" H 2700 3600 50  0001 C CNN
	1    2700 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5DFD583B
P 2450 1800
F 0 "C13" V 2198 1800 50  0000 C CNN
F 1 "0.1uF" V 2289 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2488 1650 50  0001 C CNN
F 3 "~" H 2450 1800 50  0001 C CNN
	1    2450 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C14
U 1 1 5DFD58CD
P 2900 1800
F 0 "C14" V 2648 1800 50  0000 C CNN
F 1 "0.1uF" V 2739 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2938 1650 50  0001 C CNN
F 3 "~" H 2900 1800 50  0001 C CNN
	1    2900 1800
	0    1    1    0   
$EndComp
$Comp
L Device:C C17
U 1 1 5DFD58E2
P 3700 2550
F 0 "C17" H 3585 2504 50  0000 R CNN
F 1 "0.1uF" H 3585 2595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3738 2400 50  0001 C CNN
F 3 "~" H 3700 2550 50  0001 C CNN
	1    3700 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:C C18
U 1 1 5DFD5934
P 4450 2550
F 0 "C18" H 4335 2504 50  0000 R CNN
F 1 "10uF 10v" H 4335 2595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4488 2400 50  0001 C CNN
F 3 "~" H 4450 2550 50  0001 C CNN
	1    4450 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3700 2700 3300 2700
Wire Wire Line
	3700 2400 3450 2400
Wire Wire Line
	3450 2400 3450 2550
Wire Wire Line
	3450 2550 3300 2550
Wire Wire Line
	4450 2700 4200 2700
Connection ~ 3700 2700
Wire Wire Line
	5050 2400 4450 2400
Wire Wire Line
	2100 3550 1900 3550
Wire Wire Line
	1900 3400 2100 3400
Text GLabel 3500 2850 2    50   Input ~ 0
OUT1A
Text GLabel 7700 2800 2    50   Input ~ 0
OUT2A
Text GLabel 7700 2950 2    50   Input ~ 0
OUT2B
Wire Wire Line
	3500 3450 3300 3450
Wire Wire Line
	3500 3300 3300 3300
Wire Wire Line
	3500 3000 3300 3000
Wire Wire Line
	3500 2850 3300 2850
Wire Wire Line
	2750 2100 2750 1800
Wire Wire Line
	2600 1800 2600 2100
Wire Wire Line
	2450 2100 2450 1950
Wire Wire Line
	2450 1950 2300 1950
Wire Wire Line
	2300 1950 2300 1800
Wire Wire Line
	3050 1800 3050 1950
Wire Wire Line
	3050 1950 2900 1950
Wire Wire Line
	2900 1950 2900 2100
Wire Wire Line
	2700 3950 2700 3750
Wire Wire Line
	4150 3750 4250 3750
$Comp
L power:GNDPWR #PWR032
U 1 1 5E12BDAD
P 2700 3950
F 0 "#PWR032" H 2700 3750 50  0001 C CNN
F 1 "GNDPWR" H 2704 3796 50  0000 C CNN
F 2 "" H 2700 3900 50  0001 C CNN
F 3 "" H 2700 3900 50  0001 C CNN
	1    2700 3950
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR026
U 1 1 5E17E7E5
P 4200 2700
F 0 "#PWR026" H 4200 2550 50  0001 C CNN
F 1 "VCC" H 4217 2873 50  0000 C CNN
F 2 "" H 4200 2700 50  0001 C CNN
F 3 "" H 4200 2700 50  0001 C CNN
	1    4200 2700
	1    0    0    -1  
$EndComp
Connection ~ 4200 2700
Wire Wire Line
	4200 2700 3700 2700
$Comp
L power:GNDPWR #PWR030
U 1 1 5E17FD3B
P 4250 3900
F 0 "#PWR030" H 4250 3700 50  0001 C CNN
F 1 "GNDPWR" H 4254 3746 50  0000 C CNN
F 2 "" H 4250 3850 50  0001 C CNN
F 3 "" H 4250 3850 50  0001 C CNN
	1    4250 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR028
U 1 1 5E06BC9D
P 1900 3650
F 0 "#PWR028" H 1900 3450 50  0001 C CNN
F 1 "GNDPWR" H 1904 3496 50  0000 C CNN
F 2 "" H 1900 3600 50  0001 C CNN
F 3 "" H 1900 3600 50  0001 C CNN
	1    1900 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 3650 1900 3550
Wire Wire Line
	1900 3550 1900 3400
Connection ~ 1900 3550
Wire Wire Line
	4150 3150 4150 3600
Wire Wire Line
	3300 3600 4150 3600
Connection ~ 4150 3600
Wire Wire Line
	4150 3600 4150 3750
Wire Wire Line
	3300 3150 4150 3150
Text GLabel 3500 3000 2    50   Input ~ 0
OUT1B
Text GLabel 3500 3300 2    50   Input ~ 0
OUT1A
Text GLabel 3500 3450 2    50   Input ~ 0
OUT1B
$Comp
L power:GNDPWR #PWR022
U 1 1 5E071657
P 5050 2400
F 0 "#PWR022" H 5050 2200 50  0001 C CNN
F 1 "GNDPWR" H 5054 2246 50  0000 C CNN
F 2 "" H 5050 2350 50  0001 C CNN
F 3 "" H 5050 2350 50  0001 C CNN
	1    5050 2400
	1    0    0    -1  
$EndComp
$Comp
L A3906:A3906 U4
U 1 1 5E071FA6
P 6900 2850
F 0 "U4" H 6900 1914 50  0000 C CNN
F 1 "A3906" H 6900 1823 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.5x2.5mm_ThermalVias" H 6900 3550 50  0001 C CNN
F 3 "" H 6900 3550 50  0001 C CNN
	1    6900 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5E071FAD
P 6650 1750
F 0 "C11" V 6398 1750 50  0000 C CNN
F 1 "0.1uF" V 6489 1750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6688 1600 50  0001 C CNN
F 3 "~" H 6650 1750 50  0001 C CNN
	1    6650 1750
	0    1    1    0   
$EndComp
$Comp
L Device:C C12
U 1 1 5E071FB4
P 7100 1750
F 0 "C12" V 6848 1750 50  0000 C CNN
F 1 "0.1uF" V 6939 1750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7138 1600 50  0001 C CNN
F 3 "~" H 7100 1750 50  0001 C CNN
	1    7100 1750
	0    1    1    0   
$EndComp
$Comp
L Device:C C15
U 1 1 5E071FBB
P 7900 2500
F 0 "C15" H 7785 2454 50  0000 R CNN
F 1 "0.1uF" H 7785 2545 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7938 2350 50  0001 C CNN
F 3 "~" H 7900 2500 50  0001 C CNN
	1    7900 2500
	-1   0    0    1   
$EndComp
$Comp
L Device:C C16
U 1 1 5E071FC2
P 8650 2500
F 0 "C16" H 8535 2454 50  0000 R CNN
F 1 "10uF 10v" H 8535 2545 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8688 2350 50  0001 C CNN
F 3 "~" H 8650 2500 50  0001 C CNN
	1    8650 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 2650 7500 2650
Wire Wire Line
	7900 2350 7650 2350
Wire Wire Line
	7650 2350 7650 2500
Wire Wire Line
	7650 2500 7500 2500
Wire Wire Line
	8650 2650 8400 2650
Connection ~ 7900 2650
Wire Wire Line
	9250 2350 8650 2350
Wire Wire Line
	6300 3500 6100 3500
Wire Wire Line
	6100 3350 6300 3350
Wire Wire Line
	7700 3400 7500 3400
Wire Wire Line
	7700 3250 7500 3250
Wire Wire Line
	7700 2950 7500 2950
Wire Wire Line
	7700 2800 7500 2800
Wire Wire Line
	6950 2050 6950 1750
Wire Wire Line
	6800 1750 6800 2050
Wire Wire Line
	6650 2050 6650 1900
Wire Wire Line
	6650 1900 6500 1900
Wire Wire Line
	6500 1900 6500 1750
Wire Wire Line
	7250 1750 7250 1900
Wire Wire Line
	7250 1900 7100 1900
Wire Wire Line
	7100 1900 7100 2050
Wire Wire Line
	6900 3900 6900 3700
Wire Wire Line
	8350 3700 8450 3700
$Comp
L power:GNDPWR #PWR031
U 1 1 5E071FE4
P 6900 3900
F 0 "#PWR031" H 6900 3700 50  0001 C CNN
F 1 "GNDPWR" H 6904 3746 50  0000 C CNN
F 2 "" H 6900 3850 50  0001 C CNN
F 3 "" H 6900 3850 50  0001 C CNN
	1    6900 3900
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR025
U 1 1 5E071FEA
P 8400 2650
F 0 "#PWR025" H 8400 2500 50  0001 C CNN
F 1 "VCC" H 8417 2823 50  0000 C CNN
F 2 "" H 8400 2650 50  0001 C CNN
F 3 "" H 8400 2650 50  0001 C CNN
	1    8400 2650
	1    0    0    -1  
$EndComp
Connection ~ 8400 2650
Wire Wire Line
	8400 2650 7900 2650
Wire Wire Line
	8450 3850 8450 3700
$Comp
L power:GNDPWR #PWR029
U 1 1 5E071FF3
P 8450 3850
F 0 "#PWR029" H 8450 3650 50  0001 C CNN
F 1 "GNDPWR" H 8454 3696 50  0000 C CNN
F 2 "" H 8450 3800 50  0001 C CNN
F 3 "" H 8450 3800 50  0001 C CNN
	1    8450 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR027
U 1 1 5E071FF9
P 6100 3600
F 0 "#PWR027" H 6100 3400 50  0001 C CNN
F 1 "GNDPWR" H 6104 3446 50  0000 C CNN
F 2 "" H 6100 3550 50  0001 C CNN
F 3 "" H 6100 3550 50  0001 C CNN
	1    6100 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3600 6100 3500
Wire Wire Line
	6100 3500 6100 3350
Connection ~ 6100 3500
Wire Wire Line
	8350 3100 8350 3550
Wire Wire Line
	7500 3550 8350 3550
Connection ~ 8350 3550
Wire Wire Line
	8350 3550 8350 3700
Wire Wire Line
	7500 3100 8350 3100
$Comp
L power:GNDPWR #PWR021
U 1 1 5E072012
P 9250 2350
F 0 "#PWR021" H 9250 2150 50  0001 C CNN
F 1 "GNDPWR" H 9254 2196 50  0000 C CNN
F 2 "" H 9250 2300 50  0001 C CNN
F 3 "" H 9250 2300 50  0001 C CNN
	1    9250 2350
	1    0    0    -1  
$EndComp
Text GLabel 7700 3250 2    50   Input ~ 0
OUT2A
Text GLabel 7700 3400 2    50   Input ~ 0
OUT2B
Text GLabel 5400 4850 2    50   Input ~ 0
OUT1A
Text GLabel 5400 4950 2    50   Input ~ 0
OUT1B
Text GLabel 7650 4900 2    50   Input ~ 0
OUT2A
Text GLabel 7650 5000 2    50   Input ~ 0
OUT2B
Text GLabel 6300 2650 0    50   BiDi ~ 0
D5
Text GLabel 6300 2800 0    50   BiDi ~ 0
D6
Text GLabel 6300 2950 0    50   BiDi ~ 0
D5
Text GLabel 6300 3100 0    50   BiDi ~ 0
D6
Text GLabel 2100 3000 0    50   BiDi ~ 0
D9
Text GLabel 2100 3150 0    50   BiDi ~ 0
D10
Text GLabel 2100 2700 0    50   BiDi ~ 0
D9
Text GLabel 2100 2850 0    50   BiDi ~ 0
D10
Wire Wire Line
	4250 3750 4250 3900
Text GLabel 1850 2550 1    50   BiDi ~ 0
D7
Text GLabel 6050 2500 1    50   BiDi ~ 0
D7
$Comp
L power:GND #PWR024
U 1 1 5E16CBD2
P 1400 2600
F 0 "#PWR024" H 1400 2350 50  0001 C CNN
F 1 "GND" H 1405 2427 50  0000 C CNN
F 2 "" H 1400 2600 50  0001 C CNN
F 3 "" H 1400 2600 50  0001 C CNN
	1    1400 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E16DEC9
P 1600 2550
AR Path="/5E16DEC9" Ref="R?"  Part="1" 
AR Path="/5E12A18E/5E16DEC9" Ref="R?"  Part="1" 
AR Path="/5E44C6CF/5E16DEC9" Ref="R18"  Part="1" 
F 0 "R18" H 1670 2596 50  0000 L CNN
F 1 "10K" H 1670 2505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1530 2550 50  0001 C CNN
F 3 "~" H 1600 2550 50  0001 C CNN
	1    1600 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	1450 2550 1400 2550
Wire Wire Line
	1400 2550 1400 2600
Wire Wire Line
	1750 2550 2100 2550
$Comp
L power:GND #PWR023
U 1 1 5E174BF1
P 5600 2550
F 0 "#PWR023" H 5600 2300 50  0001 C CNN
F 1 "GND" H 5605 2377 50  0000 C CNN
F 2 "" H 5600 2550 50  0001 C CNN
F 3 "" H 5600 2550 50  0001 C CNN
	1    5600 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E174BF7
P 5800 2500
AR Path="/5E174BF7" Ref="R?"  Part="1" 
AR Path="/5E12A18E/5E174BF7" Ref="R?"  Part="1" 
AR Path="/5E44C6CF/5E174BF7" Ref="R17"  Part="1" 
F 0 "R17" H 5870 2546 50  0000 L CNN
F 1 "10K" H 5870 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5730 2500 50  0001 C CNN
F 3 "~" H 5800 2500 50  0001 C CNN
	1    5800 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 2500 5600 2500
Wire Wire Line
	5600 2500 5600 2550
Wire Wire Line
	5950 2500 6300 2500
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 621CFE32
P 5200 4850
F 0 "J2" H 5306 5028 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5306 4937 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x02_P2.00mm_Vertical" H 5200 4850 50  0001 C CNN
F 3 "~" H 5200 4850 50  0001 C CNN
	1    5200 4850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 621CFE9A
P 7450 4900
F 0 "J4" H 7556 5078 50  0000 C CNN
F 1 "Conn_01x02_Male" H 7556 4987 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x02_P2.00mm_Vertical" H 7450 4900 50  0001 C CNN
F 3 "~" H 7450 4900 50  0001 C CNN
	1    7450 4900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
