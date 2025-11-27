# VescUart

Arduino library for interfacing with a VESC over UART. This library is based upon the works of many. The library is tested on a Teensy 4, and is updated for VESC firmware FW5+. The library is not nessecary backwards compatible with older versions of VESC firmware, so please update to the newest firmware available to your VESC.

The library supports only a small amount of features available to the VESC. You are welcome to make a pull request if you integrate new functionality and I will do my best to merge. 

## CAN BUS support

CAN BUS is now supported, such that you can communcate with multiple VESCs over a single UART port. All methods can be called with a CAN ID, and the main VESC will forward the command to the desired CAN Id. 

You can't use a CAN bus ID of 0 for this library, as this is used to refer to the local device; start numbering at 1.

## Supported Hardware
* Arduino (Uno, Mega, Nano, Micro, Leonardo, etc.)
* Arduino Nano 33 IoT (and other SAMD21 boards)
* ESP8266
* ESP32
* Teensy

## Wiring
### Arduino Uno / Nano (SoftwareSerial)
Not recommended for high baud rates.
* VESC TX -> Arduino Pin 2 (RX)
* VESC RX -> Arduino Pin 3 (TX)

### Arduino Mega / Leonardo / Micro (HardwareSerial)
* VESC TX -> Arduino RX1 (Pin 19 on Mega)
* VESC RX -> Arduino TX1 (Pin 18 on Mega)

### Arduino Nano 33 IoT
* VESC TX -> Arduino RX (Pin 0)
* VESC RX -> Arduino TX (Pin 1)
* **Note:** Use `Serial1` in your code for VESC communication. `Serial` is used for USB debugging.

## Installation
1. Download the repository as ZIP
2. Open Arduino IDE -> Sketch -> Include Library -> Add .ZIP Library...
3. Select the downloaded ZIP file

## Usage
  
Initialize VescUart class and select Serial port for UART communication.  
  
```cpp
#include <VescUart.h>

VescUart UART;

void setup() {
  Serial.begin(115200);

  while (!Serial) {;}

  UART.setSerialPort(&Serial);
}
```
  
Getting VESC telemetry:
  
```cpp
if ( UART.getVescValues() ) {
  Serial.println(UART.data.rpm);
  Serial.println(UART.data.inpVoltage);
  Serial.println(UART.data.ampHours);
  Serial.println(UART.data.tachometerAbs);
}
```
  
You can find example usage and more information in the examples directory.  
