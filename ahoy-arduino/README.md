# ahoy-arduino
helper library for arduino
//https://espeasy.readthedocs.io/en/latest/Reference/GPIO.html#best-pins-to-use-on-esp8266


### ESP-8266 setup instructions
1. download drivers, depends on board
  - [CH340](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)
  - [silabs](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
  - [ftdi](https://ftdichip.com/drivers/vcp-drivers/)
1. Arduino -> File -> Preferences -> Additional board manager urls
  -  `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
  - or for esp32 as well `https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json`
1. Arduino -> Tools -> Board -> Boards Manager -> search `esp` -> install `esp32` && `esp8266`
1. Arduino -> Tools -> Board -> ESP8266 -> `Generic ESP8266`
1. Arduino -> Tools -> Flash Size -> `4MB - FS:2MB OTA`


## Patch Notes

- 0.5 - 
  - changes to captain messages
  - auto detect and support for up to 8 arduino devices
  - use switch for access point mode
- 0.4 - Rewritten google iot library, slimmer and more explicit functionality
- 0.3 - led controller makes wire requests from esp8266
  - This is to solve the issue of fastled disabling interrupts during transmissions
  - Also frees up serial for debugging only
- 0.2 - Led segments and patterns
- 0.1 - Experiments


## Bugs
- 0.5
	- If config is empty, an unhandled exception is thrown

## Setup Instructions


 Google cloud pub sub allows about 3.7 pubsub messages (up to a kilobyte) per second
this includes pushes and pulls
after that its $40 / terabyte

 You need to set certificates to All SSL cyphers and you may need to
 increase memory settings in Arduino/cores/esp8266/StackThunk.cpp:
C:\Users\petey\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.6.3\cores\esp8266\StackThunk.cpp
 #define _stackSize (6748/4)
   https://github.com/esp8266/Arduino/issues/6811

## Wire Protocol

Default buffers:
|        Type        | Size (bytes) |
| :----------------: | :----------: |
|       serial       |      64      |
|        wire        |      32      |
|    arduino mqtt    |     128      |
| google mqtt config |    64000     |

Because of size limitations, and need for led controller to poll for requests, the following happens:

1. led controller asks for has message
2. 
3. if wifi has message wifi sends bytes one at a time, beginning with '[' and ending with ']'

## ESP8266 Pins


### Uno R3 + WIFI Dual Board
https://robotdyn.com/uno-wifi-r3-atmega328p-esp8266-32mb-flash-usb-ttl-ch340g-micro-usb.html

### Wemos D1 Mini
https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
| Label |  Pin  |
| :---: | :---: |
|  TX   |   1   |
|  RX   |   3   |
|  D1   |   5   |
|  D2   |   4   |
|  D3   |   0   |
|  D4   |   2   |
|  D0   |  16   |
|  D5   |  14   |
|  D6   |  12   |
|  D7   |  13   |
|  D8   |  15   |





## Test devices

|  Name   |  Board Type   |   ip address   |    mac address    |
| :-----: | :-----------: | :------------: | :---------------: |
|  study  | Wemos D1 Mini | 192.168.86.200 | 4C:11:AE:03:E9:D4 |
| kitchen |  Generic 4MB  | 192.168.86.201 | 60:01:94:79:40:f8 |
|         |               |                |                   |
|         |               |                |                   |


## TODO

- Auto Assign default device SSID, like external serial number