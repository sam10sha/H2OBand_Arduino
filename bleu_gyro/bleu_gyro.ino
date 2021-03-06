#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_BLE.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
#include "bleuart_cmdmode.h"
#include "gyroscope.h"

void setup() {
  while (!Serial);  // required for Flora & Micro
  delay(500);
  Serial.begin(115200);
  
  //bleuart_setup();
  gyroscope_setup();
}

void loop() {
  //gyroscope_operate();
  
  int accel_vals[3];
  int mag_vals[3];
  int gyro_vals[3];
  int temp;
  
  gyroscope_retrieve_values(accel_vals, mag_vals, gyro_vals, &temp);
  
  String msg = "Accel vals:\n";
  for(char i = 0; i < 3; i++) {
    msg += String(accel_vals[i]);
    if(i < 2)
      msg += ", ";
  }
  msg += "\n";  
  msg += "Mag vals:\n";
  for(char i = 0; i < 3; i++) {
    msg += String(mag_vals[i]);
    if(i < 2)
      msg += ", ";
  }
  msg += "\n";  
  msg += "Gyro vals:\n";
  for(char i = 0; i < 3; i++) {
    msg += String(gyro_vals[i]);
    if(i < 2)
      msg += ", ";
  }
  msg += "\n\n";
  
  Serial.println(msg);
  
  delay(1000);
}
