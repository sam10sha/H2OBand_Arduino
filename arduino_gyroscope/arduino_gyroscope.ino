#include <Wire.h>

//const byte MPU     = 0x1D;
const byte MPU     = 0x6B;
const byte magn_vals[] = {0x08, 0x0A, 0x0C};
const byte accel_vals[] = {0x28, 0x2A, 0x2C};

void setupMPU();

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while(!Serial) {}
  
  Serial.println("Setting up MPU");
  setupMPU();
  
  Serial.println("Start data");
}

void loop() {
  int i;
  byte value, byte_num;
  Serial.println("Accelerometer values:");
  Serial.print("( ");
  for(i = 0; i < 3; i++) {
    Wire.beginTransmission(MPU);
    Wire.write(accel_vals[i]);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 2);
    
    byte_num = 0;
    value = 0;
    while(Wire.available())
      value += Wire.read() << (byte_num++ * 8);
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.println(")");
  
  Serial.println("Magnetometer values:");
  Serial.print("( ");
  for(i = 0; i < 3; i++) {
    Wire.beginTransmission(MPU);
    Wire.write(magn_vals[i]);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 2);
    
    byte_num = 0;
    value = 0;
    while(Wire.available())
      value += Wire.read() << (byte_num++ * 8);
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.println(")");  
  Serial.println("");
  
  delay(1000);
}


void setupMPU(){
  byte value;
  
  
  //CONFIGURATIONS FOR GYROSCOPE
  Serial.println("Beginning transmission");
  Wire.beginTransmission(MPU);
  Serial.println("Sending address");
  Wire.write(0x20);
  Serial.println("Ending transmission");
  Wire.endTransmission();
  Serial.println("Requesting 1 byte");
  Wire.requestFrom(MPU, 1);
  Serial.println("Waiting for response");
  if(Wire.available()) {
    value = Wire.read();
    Serial.print("Value: ");
    Serial.println(value);
    Wire.beginTransmission(MPU);
    Wire.write(0x20);
    Wire.write(value | 0x08);
    Wire.endTransmission();
  }
  
  //CONFIGURATIONS FOR ACCELEROMETER pg 55
  Serial.println("Beginning transmission");
  Wire.beginTransmission(MPU);
  Serial.println("Sending address");
  Wire.write(0x20);
  Serial.println("Ending transmission");
  Wire.endTransmission();
  Serial.println("Requesting 1 byte");
  Wire.requestFrom(MPU, 1);
  Serial.println("Waiting for response");
  if(Wire.available()) {
    value = Wire.read();
    Serial.print("Value: ");
    Serial.println(value);
    Wire.beginTransmission(MPU);
    Wire.write(0x20);
    Wire.write(value | 0x08);
    Wire.endTransmission();
  }
}
