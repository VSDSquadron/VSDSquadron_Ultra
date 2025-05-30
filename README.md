# Pin Connections between VSD32-S3 and FTDI232 for WiFi Setup

| VSD32-S3 signal / pin | Connect to        | Notes                                                         |
|-----------------------|-------------------|---------------------------------------------------------------|
| **WiFi_P_Tx**         | FTDI232 **Rx**    | UART transmit from VSD32-S3 to FTDI232 receive               |
| **WiFi_P_Rx**         | FTDI232 **Tx**    | UART receive on VSD32-S3 from FTDI232 transmit               |
| **GND**               | FTDI232 **GND**   | Common ground reference                                      |
| **WiFi_P_BOOT**       | VSD32-S3 **GND**  | Pull BOOT low to place ESP32-C3 module in normal run mode    |


# squadron_S3

Detailed steps : [Setup Guide](https://docs.espressif.com/projects/esp-at/en/latest/esp32c3/Get_Started/Downloading_guide.html)

## Overview
- download flash tool
- download AT firmware
- set strapping pins
- flash over UART0 after putting in UART BOOT MODE
- unset strapping pins
- reboot
- AT over UART 1 


[Hardware reference](https://docs.espressif.com/projects/esp-at/en/latest/esp32c3/Get_Started/Hardware_connection.html)

Based on above Hardware reference make the following connections

![alt text](image-1.png)



![alt text](image.png)

## Reference
[AT Commands](https://docs.espressif.com/projects/esp-at/en/latest/esp32c3/AT_Command_Set/index.html)
