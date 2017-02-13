#include <Wire.h>

//const byte MPU     = 0x1D;
const byte MPU     = 0x6B;
const byte magn_vals[] = {0x08, 0x0A, 0x0C};
const byte accel_vals[] = {0x28, 0x2A, 0x2C};

bool setupMPU();
void getMPUValues(const byte* registers, int num_registers, byte* results, int num_results);


void setup() {
  Wire.begin();
  Serial.begin(9600);
  while(!Serial) {}
  
  Serial.println("Setting up MPU");
  bool setup_complete = setupMPU();
  while(!setup_complete) {}
  
  Serial.println("Start data");
}

void loop() {
  const int NUM_VALUES= 3;
  int i;
  byte results[NUM_VALUES];
  
  /* Serial.print("Magnetometer values:\n{");
  for(i = 0; i < NUM_VALUES; i++)
    results[i] = 0x00;
  getMPUValues(magn_vals, NUM_VALUES, results, NUM_VALUES);
  for(i = 0; i < NUM_VALUES; i++) {
    Serial.print(results[i]);
    if(i < NUM_VALUES - 1)
      Serial.print(", ");
  }
  Serial.println("}\n"); */
  
  
  Serial.print("Accelerometer values:\n{");
  for(i = 0; i < NUM_VALUES; i++)
    results[i] = 0x00;
  getMPUValues(accel_vals, NUM_VALUES, results, NUM_VALUES);
  for(i = 0; i < NUM_VALUES; i++) {
    Serial.print(results[i]);
    if(i < NUM_VALUES - 1)
      Serial.print(", ");
  }
  Serial.println("}\n");
  
  delay(1000);
}


bool setupMPU(){
  byte value;
  
  //CONFIGURATIONS
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
    
    return true;
  }
  
  return false;
}

void getMPUValues(const byte* registers, int num_registers, byte* results, int num_results) {
  byte i,          //counter for register
        value,     //current value received from MPU
        byte_num,  //current byte number received from MPU
        current_num_results;  //total number of results received from MPU
  for(i = 0, current_num_results = 0; i < num_registers && current_num_results < num_results;
                  i++) {
    Wire.beginTransmission(MPU);
    Wire.write(registers[i]);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 2);
    
    byte_num = 0;
    value = 0;
    while(Wire.available())
      value += Wire.read() << (byte_num++ * 8);
    results[current_num_results++] = value;
  }
}
