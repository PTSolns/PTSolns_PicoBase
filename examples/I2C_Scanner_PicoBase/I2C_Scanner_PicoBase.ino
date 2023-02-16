// I2C scanner for Pico Base (and variations of Pico Base)
// Laste update: Feb 15, 2023
//
// DESCRIPTION
// This sketch scans both the I2C0 bus (I2C bus on Port 0) and the I2C1 bus (I2C bus on Port 1) for any connected devices.
// As the I2C SDA/SCL pins are hardwired for the Pico Base, the respective pins have to be defined and cannot be changed.
//
// This sketch is based on the sketch by Carter Nelson, found here: https://learn.adafruit.com/scanning-i2c-addresses/arduino

#include <Wire.h>

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

  Serial.begin(9600);
  Serial.println("Starting I2C scanner for Pico Base ...");
  Serial.println(" ");
}


void loop() {
  byte error, address;
  int nDevices;

  // Scanning on I2C0 Bus
  Serial.println("Scanning on I2C0 Bus ...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0){
      Serial.print("   I2C0 device found at address: 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4){
      Serial.print("   Unknown error at address: 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);
    }    
  }

  if (nDevices == 0) {
    Serial.println("   No I2C0 devices found.");
  }
  
  Serial.println("   Done scanning on I2C0 Bus.");
  


  // Scanning on I2C1 Bus
  Serial.println(" ");
  Serial.println("Scanning on I2C1 Bus ...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ){
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();

    if (error == 0){
      Serial.print("   I2C1 device found at address: 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4){
      Serial.print("   Unknown error at address: 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);
    }    
  }

  if (nDevices == 0) {
    Serial.println("   No I2C1 devices found.");
  }

  Serial.println("   Done scanning on I2C1 Bus.");
  

  Serial.println(" ");
  delay(5000); 
  Serial.println("*********");
  Serial.println(" ");
}