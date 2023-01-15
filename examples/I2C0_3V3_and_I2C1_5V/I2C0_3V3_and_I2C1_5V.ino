// EXAMPLE: I2C0 3V3 and I2C1 5V
// Last update: Jan 10, 2023
// contact@PTSolns
//
// DESCRIPTION
// This example builds on the previous example "LCD_on_5V_I2C". Please see that example before proceeding.
// In this example will we connect a 3.3V sensor to the I2C bus on port 0, and display the results on an LCD connected via 5V I2C on port 1.
// Any 3.3V sensor that can be connected via I2C will work in this example. However, we will use the Sparkfun Atmospheric Sensor BME280.
// This sensor uses the Qwiic connector that allows the user to connect a string of I2C sensors.
// The Pico Base and Pico Base + Proto have an onboard QWIIC connector and thus the user can easily add this sensor.
//
// The 3V3 I2C pins are hardwired to the Pi Pico/Pi Pico W pins. The configuration is as follows:
// SCL on Port 0 -> GP21
// SDA on Port 0 -> GP20
//
// The 5V I2C pins are hardwired to the Pi Pico/Pi Pico W pins. The configuration is as follows:
// SCL on Port 1 -> GP19
// SDA on Port 1 -> GP18
//
// HARDWARE CONFIGURATION
// This example will work for both Pico Base and Pico Base + Proto. However, if uisng the + Proto, then the 1602 LCD can be mounted to the mounting holes.
// A 4-Pin 2.54mm screw terminal has to be installed in the corresponding footprint for the 5V I2C. The location of which is marked on the PCB.
// Connect the I2C wires, 5V and GND from the LCD with I2C backpack to the corresponding marked pins on the PCB via the 4-Pin screw terminal.
// Finally, simply plug the sensor into the Qwiic connector.
//
// TROUBLESHOOTING
// 1) Check contrast on the back of the LCD module. Adjust onboard potentiometer.
// 2) With a multimeter, check voltages of 5V Pin, SDA1 and SCL1. They should read around 5V.
// 3) Check using an I2C scanner for Wire1 that the LCD can be found and has address 0x27.
// 4) Try a different sensor.
// 5) If all fails, upload a standard example (not I2C, LCD) and ensure Pico is working properly.
//
// REFERENCES
// Sparkfun BME280 sensor: https://github.com/sparkfun/SparkFun_BME280_Arduino_Library

#include <Wire.h>
#include "LiquidCrystal_PCF8574.h"
#include "SparkFunBME280.h"

BME280 mySensor;

LiquidCrystal_PCF8574 lcd(0x27);  // Set the LCD address to 0x27 

// Setting the pin numbers for I2C on port 0. Pin assignments are hardwired and therefore should not be changed here.
const byte SDA_3V3_pin = 20;
const byte SCL_3V3_pin = 21;

// Setting the pin numbers for I2C on port 1. Pin assignments are hardwired and therefore should not be changed here.
const byte SDA_5V_pin = 18;
const byte SCL_5V_pin = 19;

void setup() {

  // Set I2C on port 0 pins for Wire. Need to set the I2C pins, as we are not using the Pico defaults for I2C0.
  Wire.setSDA(SDA_3V3_pin);
  Wire.setSCL(SCL_3V3_pin);
  Wire.begin();
  
  // Set I2C on port 1 pins for Wire1. Need to set the I2C pins, as we are not using the Pico defaults for I2C1.
  Wire1.setSDA(SDA_5V_pin);
  Wire1.setSCL(SCL_5V_pin);
  Wire1.begin();

  // Sensor BME280
  mySensor.setI2CAddress(0x77); 
  mySensor.beginI2C()

  // Start the LCD
  lcd.begin(16,2,Wire1); // Note, we are telling the LCD to use Wire1 for I2C.
  lcd.setBacklight(255); // Full brightness.
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Temp: " + String(mySensor.readTempC()));
  lcd.setCursor(0,1);
  lcd.print("Hum: " + String(mySensor.readFloatHumidity()));

  delay(100);
}
