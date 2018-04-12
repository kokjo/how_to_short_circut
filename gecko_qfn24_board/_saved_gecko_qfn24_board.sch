EESchema Schematic File Version 2
LIBS:gecko_qfn24_board-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:efm32hg309
LIBS:gecko_qfn24_board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L EFM32HG309 U1
U 1 1 5A79B5EE
P 5325 4450
F 0 "U1" H 5275 4400 60  0000 C CNN
F 1 "EFM32HG309" H 5975 5125 39  0000 C CNN
F 2 "Housings_DFN_QFN:QFN-24-1EP_5x5mm_Pitch0.65mm" H 5325 4450 60  0001 C CNN
F 3 "" H 5325 4450 60  0000 C CNN
	1    5325 4450
	1    0    0    -1  
$EndComp
$Comp
L USB_B-RESCUE-gecko_qfn24_board P3
U 1 1 5A79B6A8
P 7550 3500
F 0 "P3" H 7750 3300 50  0000 C CNN
F 1 "USB_B" H 7500 3700 50  0000 C CNN
F 2 "Connectors_USB:USB_Micro-B_Molex_47346-0001" V 7500 3400 50  0001 C CNN
F 3 "" V 7500 3400 50  0000 C CNN
	1    7550 3500
	0    1    1    0   
$EndComp
$Comp
L R_Small R1
U 1 1 5A79B80C
P 6825 3375
F 0 "R1" V 6750 3325 50  0000 L CNN
F 1 "15" V 6825 3325 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" H 6825 3375 50  0001 C CNN
F 3 "" H 6825 3375 50  0000 C CNN
	1    6825 3375
	0    1    1    0   
$EndComp
$Comp
L R_Small R2
U 1 1 5A79B89A
P 6825 3500
F 0 "R2" V 6900 3475 50  0000 L CNN
F 1 "15" V 6825 3450 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" H 6825 3500 50  0001 C CNN
F 3 "" H 6825 3500 50  0000 C CNN
	1    6825 3500
	0    1    1    0   
$EndComp
$Comp
L C_Small C2
U 1 1 5A79BC32
P 6925 4100
F 0 "C2" H 6935 4170 50  0000 L CNN
F 1 "1uF" H 6935 4020 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6925 4100 50  0001 C CNN
F 3 "" H 6925 4100 50  0000 C CNN
	1    6925 4100
	1    0    0    -1  
$EndComp
$Comp
L C_Small C1
U 1 1 5A79BCA8
P 6675 4300
F 0 "C1" V 6625 4125 50  0000 L CNN
F 1 "1uF" V 6725 4125 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6675 4300 50  0001 C CNN
F 3 "" H 6675 4300 50  0000 C CNN
	1    6675 4300
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR01
U 1 1 5A79BEC6
P 7100 3800
F 0 "#PWR01" H 7100 3650 50  0001 C CNN
F 1 "+3V3" H 7100 3940 50  0000 C CNN
F 2 "" H 7100 3800 50  0000 C CNN
F 3 "" H 7100 3800 50  0000 C CNN
	1    7100 3800
	1    0    0    -1  
$EndComp
$Comp
L C_Small C3
U 1 1 5A79BF4C
P 7875 3800
F 0 "C3" H 7885 3870 50  0000 L CNN
F 1 "4.7uF" H 7885 3720 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7875 3800 50  0001 C CNN
F 3 "" H 7875 3800 50  0000 C CNN
	1    7875 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5A79C156
P 7100 4525
F 0 "#PWR02" H 7100 4275 50  0001 C CNN
F 1 "GND" H 7100 4375 50  0000 C CNN
F 2 "" H 7100 4525 50  0000 C CNN
F 3 "" H 7100 4525 50  0000 C CNN
	1    7100 4525
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 5A79C1DB
P 8150 3350
F 0 "#PWR03" H 8150 3200 50  0001 C CNN
F 1 "+5V" H 8150 3490 50  0000 C CNN
F 2 "" H 8150 3350 50  0000 C CNN
F 3 "" H 8150 3350 50  0000 C CNN
	1    8150 3350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X09 P1
U 1 1 5A79C357
P 3650 4225
F 0 "P1" H 3650 4725 50  0000 C CNN
F 1 "CONN_01X09" V 3750 4225 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x09" H 3650 4225 50  0001 C CNN
F 3 "" H 3650 4225 50  0000 C CNN
	1    3650 4225
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X09 P2
U 1 1 5A79C440
P 3650 3225
F 0 "P2" H 3650 3725 50  0000 C CNN
F 1 "CONN_01X09" V 3750 3225 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x09" H 3650 3225 50  0001 C CNN
F 3 "" H 3650 3225 50  0000 C CNN
	1    3650 3225
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR04
U 1 1 5A79CB64
P 4000 3750
F 0 "#PWR04" H 4000 3500 50  0001 C CNN
F 1 "GND" H 4000 3600 50  0000 C CNN
F 2 "" H 4000 3750 50  0000 C CNN
F 3 "" H 4000 3750 50  0000 C CNN
	1    4000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6425 3300 7250 3300
Wire Wire Line
	6425 3375 6725 3375
Wire Wire Line
	6925 3375 7250 3400
Wire Wire Line
	7250 4400 7250 3600
Wire Wire Line
	6425 4400 7875 4400
Wire Wire Line
	6425 3625 6925 3625
Wire Wire Line
	6675 3625 6675 4200
Wire Wire Line
	6675 4200 6425 4200
Wire Wire Line
	6425 3900 6675 3900
Connection ~ 6675 3900
Wire Wire Line
	6425 3975 6675 3975
Connection ~ 6675 3975
Wire Wire Line
	6425 4050 6675 4050
Connection ~ 6675 4050
Wire Wire Line
	6425 4125 6675 4125
Connection ~ 6675 4125
Wire Wire Line
	6425 4300 6575 4300
Wire Wire Line
	6775 4300 6925 4300
Wire Wire Line
	6925 4200 6925 4400
Connection ~ 6925 4400
Connection ~ 6675 3625
Wire Wire Line
	7250 3500 6925 3500
Wire Wire Line
	6425 3450 6725 3500
Wire Wire Line
	6925 3900 7100 3900
Wire Wire Line
	7100 3900 7100 3800
Connection ~ 6925 3900
Wire Wire Line
	7125 3300 7125 3150
Wire Wire Line
	7125 3150 7875 3150
Connection ~ 7250 4400
Connection ~ 7125 3300
Wire Wire Line
	7875 4400 7875 3900
Wire Wire Line
	7875 3150 7875 3700
Wire Wire Line
	7100 4400 7100 4525
Connection ~ 7100 4400
Wire Wire Line
	8150 3350 8150 3475
Wire Wire Line
	8150 3475 7875 3475
Connection ~ 7875 3475
Wire Wire Line
	4000 3525 4000 3750
Wire Wire Line
	4000 3625 3850 3625
Wire Wire Line
	3850 3525 4000 3525
Connection ~ 4000 3625
$Comp
L +5V #PWR05
U 1 1 5A79CC76
P 3875 4750
F 0 "#PWR05" H 3875 4600 50  0001 C CNN
F 1 "+5V" H 3875 4890 50  0000 C CNN
F 2 "" H 3875 4750 50  0000 C CNN
F 3 "" H 3875 4750 50  0000 C CNN
	1    3875 4750
	-1   0    0    1   
$EndComp
$Comp
L +3V3 #PWR06
U 1 1 5A79CCB7
P 4025 4750
F 0 "#PWR06" H 4025 4600 50  0001 C CNN
F 1 "+3V3" H 4025 4890 50  0000 C CNN
F 2 "" H 4025 4750 50  0000 C CNN
F 3 "" H 4025 4750 50  0000 C CNN
	1    4025 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3850 4625 3875 4625
Wire Wire Line
	3875 4625 3875 4750
Wire Wire Line
	3850 4525 4025 4525
Wire Wire Line
	4025 4525 4025 4750
Wire Wire Line
	6925 3625 6925 4000
Connection ~ 6925 4300
Wire Wire Line
	5125 3700 3850 3425
Wire Wire Line
	5125 3625 3850 3325
Wire Wire Line
	5125 3550 3850 3225
Wire Wire Line
	3850 3125 5125 4400
Wire Wire Line
	5125 3475 3850 3025
Wire Wire Line
	5125 3400 3850 2925
Wire Wire Line
	5125 3875 3850 2825
Wire Wire Line
	5125 3800 3850 3825
Wire Wire Line
	5125 3300 3850 3925
Wire Wire Line
	5125 3975 3850 4025
Wire Wire Line
	5125 4050 3850 4125
Wire Wire Line
	5125 4300 3850 4225
Wire Wire Line
	5125 4225 3850 4325
Wire Wire Line
	5125 4150 3850 4425
Wire Wire Line
	7650 3800 7650 4400
Connection ~ 7650 4400
$EndSCHEMATC
