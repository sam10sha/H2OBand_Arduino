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
  bleuart_setup();
  gyroscope_setup();
}

void loop() {
  blueart_operate();
  gyroscope_operate();
}
