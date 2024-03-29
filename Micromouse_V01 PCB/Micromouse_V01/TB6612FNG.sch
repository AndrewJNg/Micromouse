EESchema Schematic File Version 4
LIBS:Micromouse_V01-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3450 2750 3500 2750
Wire Wire Line
	3450 3350 3450 2750
Wire Wire Line
	3450 3550 3200 3550
Wire Wire Line
	3200 3650 3450 3650
Wire Wire Line
	3450 3850 3200 3850
Wire Wire Line
	3200 3950 3450 3950
Wire Wire Line
	3450 4050 3200 4050
Wire Wire Line
	3200 4150 3450 4150
Text GLabel 3200 4150 0    50   BiDi ~ 0
17
Text GLabel 3200 4050 0    50   BiDi ~ 0
16
Text GLabel 3200 3950 0    50   BiDi ~ 0
2
Text GLabel 3200 3850 0    50   BiDi ~ 0
4
Text GLabel 3200 3650 0    50   BiDi ~ 0
5
Text GLabel 3200 3550 0    50   BiDi ~ 0
15
Wire Wire Line
	4650 4050 5100 4050
Wire Wire Line
	5100 3950 4650 3950
Wire Wire Line
	5100 3550 4650 3550
Wire Wire Line
	5100 3450 4650 3450
Wire Wire Line
	4450 2650 4450 2750
$Comp
L power:VCC #PWR?
U 1 1 62A8A5C9
P 4450 2650
AR Path="/62A8A5C9" Ref="#PWR?"  Part="1" 
AR Path="/62A8654D/62A8A5C9" Ref="#PWR0142"  Part="1" 
F 0 "#PWR0142" H 4450 2500 50  0001 C CNN
F 1 "VCC" H 4467 2823 50  0000 C CNN
F 2 "" H 4450 2650 50  0001 C CNN
F 3 "" H 4450 2650 50  0001 C CNN
	1    4450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2650 3500 2750
Connection ~ 3500 2750
Wire Wire Line
	3500 2750 3750 2750
$Comp
L power:+3.3V #PWR?
U 1 1 62A8A5D2
P 3500 2650
AR Path="/62A8A5D2" Ref="#PWR?"  Part="1" 
AR Path="/62A8654D/62A8A5D2" Ref="#PWR0143"  Part="1" 
F 0 "#PWR0143" H 3500 2500 50  0001 C CNN
F 1 "+3.3V" H 3515 2823 50  0000 C CNN
F 2 "" H 3500 2650 50  0001 C CNN
F 3 "" H 3500 2650 50  0001 C CNN
	1    3500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4750 3750 4750
Connection ~ 3950 4750
Wire Wire Line
	3950 4900 3950 4750
$Comp
L power:GND #PWR?
U 1 1 62A8A5DB
P 3950 4900
AR Path="/62A8A5DB" Ref="#PWR?"  Part="1" 
AR Path="/62A8654D/62A8A5DB" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 3950 4650 50  0001 C CNN
F 1 "GND" H 3955 4727 50  0000 C CNN
F 2 "" H 3950 4900 50  0001 C CNN
F 3 "" H 3950 4900 50  0001 C CNN
	1    3950 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3450 4650 3350
Wire Wire Line
	4650 3650 4650 3550
Wire Wire Line
	4650 4050 4650 4150
Wire Wire Line
	4650 3950 4650 3850
$Comp
L Connector:Conn_01x02_Female J?
U 1 1 62A8A5E5
P 5300 3950
AR Path="/62A8A5E5" Ref="J?"  Part="1" 
AR Path="/62A8654D/62A8A5E5" Ref="J4"  Part="1" 
F 0 "J4" H 5327 3926 50  0000 L CNN
F 1 "Conn_01x02_Female" H 5327 3835 50  0000 L CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x02_P2.00mm_Vertical" H 5300 3950 50  0001 C CNN
F 3 "~" H 5300 3950 50  0001 C CNN
	1    5300 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J?
U 1 1 62A8A5EC
P 5300 3450
AR Path="/62A8A5EC" Ref="J?"  Part="1" 
AR Path="/62A8654D/62A8A5EC" Ref="J2"  Part="1" 
F 0 "J2" H 5327 3426 50  0000 L CNN
F 1 "Conn_01x02_Female" H 5327 3335 50  0000 L CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_1x02_P2.00mm_Vertical" H 5300 3450 50  0001 C CNN
F 3 "~" H 5300 3450 50  0001 C CNN
	1    5300 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4750 4250 4750
Connection ~ 4250 4750
Connection ~ 4650 4050
Connection ~ 4650 3550
Wire Wire Line
	4250 4750 4150 4750
Connection ~ 4150 4750
Wire Wire Line
	4150 4750 4050 4750
Wire Wire Line
	4050 4750 3950 4750
Connection ~ 4050 4750
Connection ~ 4650 3450
Wire Wire Line
	4450 2750 4350 2750
Connection ~ 4350 2750
Wire Wire Line
	4250 2750 4150 2750
Wire Wire Line
	4350 2750 4250 2750
Connection ~ 4250 2750
Connection ~ 4650 3950
$Comp
L Driver_Motor:TB6612FNG U?
U 1 1 62A8A603
P 4050 3750
AR Path="/62A8A603" Ref="U?"  Part="1" 
AR Path="/62A8654D/62A8A603" Ref="U12"  Part="1" 
F 0 "U12" H 4050 4928 50  0000 C CNN
F 1 "TB6612FNG" H 4050 4837 50  0000 C CNN
F 2 "parts:TB6612FNG" H 4500 4350 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/us/product/linear/motordriver/detail.TB6612FNG.html" H 4500 4350 50  0001 C CNN
	1    4050 3750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
