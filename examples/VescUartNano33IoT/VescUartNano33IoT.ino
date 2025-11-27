/*
  Name:    VescUartNano33IoT.ino
  Created: 27-11-2025
  Author:  Antigravity
  Description:  Example for Arduino Nano 33 IoT (and other SAMD21 boards) to control VESC via UART.
                
  WIRING:
  - VESC RX  -> Nano 33 IoT TX (Pin 1)
  - VESC TX  -> Nano 33 IoT RX (Pin 0)
  - VESC GND -> Nano 33 IoT GND
  - VESC 5V  -> Nano 33 IoT 5V (Optional, if powering Nano from VESC)

  IMPORTANT:
  - The Nano 33 IoT uses 'Serial' for the USB connection to the computer.
  - It uses 'Serial1' for the hardware UART on pins 0 and 1.
*/

#include <VescUart.h>

/** Initiate VescUart class */
VescUart UART;

void setup() {

  /** Setup Serial port to display data on the Serial Monitor */
  Serial.begin(115200);

  /** Setup UART port (Serial1 on Nano 33 IoT) */
  Serial1.begin(115200);

  while (!Serial) {
    ; // Wait for Serial port to connect. Needed for native USB port only
  }
  
  Serial.println("Starting VescUart Nano 33 IoT Example");

  /** Define which ports to use as UART */
  UART.setSerialPort(&Serial1);
  
  /** Define which ports to use as Debug */
  UART.setDebugPort(&Serial);
}

void loop() {

  /** Call the function getVescValues() to acquire data from VESC */
  if (UART.getVescValues()) {

    Serial.println("Data fetched successfully:");
    Serial.print("RPM: "); Serial.println(UART.data.rpm);
    Serial.print("Input Voltage: "); Serial.println(UART.data.inpVoltage);
    Serial.print("Avg Motor Current: "); Serial.println(UART.data.avgMotorCurrent);
    Serial.print("Duty Cycle: "); Serial.println(UART.data.dutyCycleNow);
    Serial.println("--------------------------------");

  } else {
    Serial.println("Failed to get data!");
  }

  delay(50);
}
