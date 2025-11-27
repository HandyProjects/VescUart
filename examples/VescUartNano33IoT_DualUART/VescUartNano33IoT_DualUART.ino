/*
  Name:    VescUartNano33IoT_DualUART.ino
  Created: 27-11-2025
  Author:  Antigravity
  Description:  Example for Arduino Nano 33 IoT to control TWO VESCs via TWO SEPARATE HARDWARE UART PORTS.
                
  SETUP:
  - VESC 1: Connected to standard Serial1 (Pins 0/1).
  - VESC 2: Connected to a NEW Serial2 (Pins 12/10) created via SERCOM.

  WIRING:
  --- VESC 1 ---
  - VESC 1 RX  -> Nano 33 IoT TX (Pin 1)
  - VESC 1 TX  -> Nano 33 IoT RX (Pin 0)
  - VESC 1 GND -> Nano 33 IoT GND

  --- VESC 2 ---
  - VESC 2 RX  -> Nano 33 IoT Pin 10 (TX)
  - VESC 2 TX  -> Nano 33 IoT Pin 12 (RX)
  - VESC 2 GND -> Nano 33 IoT GND

  IMPORTANT:
  - This example uses SERCOM1 to create a second hardware serial port.
  - Pins 10 and 12 are used for this second port.
*/

#include <VescUart.h>
#include <wiring_private.h> // Needed for pinPeripheral() function

/** Initiate VescUart class for VESC 1 */
VescUart UART1;

/** Initiate VescUart class for VESC 2 */
VescUart UART2;

// --- SERCOM CONFIGURATION FOR SERIAL2 ---
// We will use SERCOM1.
// RX: Pin 12 (PA19) -> PAD[3]
// TX: Pin 10 (PA18) -> PAD[2]
Uart Serial2(&sercom1, 12, 10, SERCOM_RX_PAD_3, UART_TX_PAD_2);

void SERCOM1_Handler()
{
  Serial2.IrqHandler();
}
// ----------------------------------------

void setup() {

  /** Setup Serial port to display data on the Serial Monitor */
  Serial.begin(115200);

  /** Setup UART port 1 (Standard Serial1 on Nano 33 IoT) */
  Serial1.begin(115200);

  /** Setup UART port 2 (New Serial2 on Pins 12/10) */
  Serial2.begin(115200);

  // Assign pins to SERCOM functionality
  pinPeripheral(10, PIO_SERCOM); // TX
  pinPeripheral(12, PIO_SERCOM); // RX

  while (!Serial) {
    ; // Wait for Serial port to connect
  }
  
  Serial.println("Starting Dual UART VESC Nano 33 IoT Example");

  /** Configure VESC 1 */
  UART1.setSerialPort(&Serial1);
  UART1.setDebugPort(&Serial);

  /** Configure VESC 2 */
  UART2.setSerialPort(&Serial2);
  UART2.setDebugPort(&Serial);
}

void loop() {

  // --- CONTROL VESC 1 (Serial1) ---
  UART1.setRPM(3000); 
  
  // --- CONTROL VESC 2 (Serial2) ---
  UART2.setRPM(3000); 


  // --- READ DATA FROM VESC 1 ---
  if (UART1.getVescValues()) {
    Serial.println("--- VESC 1 (Serial1) ---");
    Serial.print("RPM: "); Serial.println(UART1.data.rpm);
    Serial.print("Voltage: "); Serial.println(UART1.data.inpVoltage);
    Serial.print("Current: "); Serial.println(UART1.data.avgMotorCurrent);
  } else {
    Serial.println("Failed to get VESC 1 data!");
  }

  delay(10); 

  // --- READ DATA FROM VESC 2 ---
  if (UART2.getVescValues()) {
    Serial.println("--- VESC 2 (Serial2) ---");
    Serial.print("RPM: "); Serial.println(UART2.data.rpm);
    Serial.print("Voltage: "); Serial.println(UART2.data.inpVoltage);
    Serial.print("Current: "); Serial.println(UART2.data.avgMotorCurrent);
  } else {
    Serial.println("Failed to get VESC 2 data!");
  }
  
  Serial.println("--------------------------------");

  delay(50);
}
