// EXAMPLE: LCD on 5V I2C
// Last update: Jan 10, 2023
// contact@PTSolns
//
// DESCRIPTION
// The Pico Base + Proto has the capability to connect to the 5V I2C bus. 
// This is done with the onboard logic level shifter (LLS) that converts the Pico 3.3V I2C signals to 5V signals.
// The Pico has two I2C busses independent of each other: I2C0 and I2C1. The Pico Base is set up to use I2C1, and hence Wire1.
// In this example the common 1602 LCD with I2C backpack is connected to the I2C 5V bus. A simple counter is displayed on the LCD.
// 
// The 5V I2C pins are hardwired to the Pi Pico/Pi Pico W pins. The configuration is as follows:
// SCL on Port 1 -> GP19
// SDA on Port 1 -> GP18
//
// HARDWARE CONFIGURATION
// This example will work for both Pico Base and Pico Base + Proto. However, if uisng the + Proto, then the 1602 LCD can be mounted to the mounting holes.
// A 4-Pin 2.54mm screw terminal has to be installed in the corresponding footprint for the 5V I2C. The location of which is marked on the PCB.
// Connect the I2C wires, 5V and GND from the LCD with I2C backpack to the corresponding marked pins on the PCB via the 4-Pin screw terminal.
//
// TROUBLESHOOTING
// 1) Check contrast on the back of the LCD module. Adjust onboard potentiometer.
// 2) With a multimeter, check voltages of 5V Pin, SDA1 and SCL1. They should read around 5V.
// 3) Check using an I2C scanner for Wire1 that the LCD can be found and has address 0x27.
// 4) If all fails, upload a standard example (not I2C, LCD) and ensure Pico is working properly.

#include <Wire.h>
#include "LiquidCrystal_PCF8574.h"

LiquidCrystal_PCF8574 lcd(0x27);  // Set the LCD address to 0x27 

int counter = 0; // Counter incremented every approx. second.

// Setting the pin numbers for I2C. Pin assignments are hardwired and therefore should not be changed here.
const byte SDA_5V_pin = 18;
const byte SCL_5V_pin = 19;

void setup() {
  // Set I2C pins for Wire1. Need to set the I2C pins, as we are not using the Pico defaults for I2C1.
  Wire1.setSDA(SDA_5V_pin);
  Wire1.setSCL(SCL_5V_pin);
  Wire1.begin();

  // Start the LCD
  lcd.begin(16,2,Wire1); // Note, we are telling the LCD to use Wire1 for I2C.
  lcd.setBacklight(255); // Full brightness.
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Counter");
  lcd.setCursor(0,1);
  lcd.print(String(counter));

  counter = counter + 1; // Increment counter

  delay(1000); // 1 second delay
}
