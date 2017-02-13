#include <Wire.h>

//const byte MPU     = 0x1D;
const byte MPU     = 0x6B;
const byte magn_vals[] = {0x08, 0x0A, 0x0C};
const byte accel_vals[] = {0x28, 0x2A, 0x2C};

//Sets up the MPU configuration registers to enable data collection from
//accelerometer/gyroscope
//
//@return  true if configuration bits were successfully set
//         false otherwise
bool setupMPU();



//Retrieves and prints out the values from specified registers in the MPU
//
//@param data_name    the label for the data to be retrieved
//@param data_addrs   the addresses of the registers to query
//@param num_addrs    the number of addresses
void printMPUVals(String data_name, const byte* data_addrs, int num_addrs);




//Retrieves the MPU values at the registers specified and stores them into the
//results array
//
//@param registers      the list of registers to query
//@param num_registers  the number of registers to query
//@param results        an empty array into which the results must be recorded
//@param num_results    the number of results to record; should be same as number of registers
//
//@return  true if all values were successfully retrieved
//         false otherwise
bool getMPUValues(const byte* registers, int num_registers, byte* results, int num_results);


void setup() {
  Wire.begin();
  Serial.begin(9600);
  //DO NOTHING IF SERIAL MONITOR IS NOT OPEN
  while(!Serial) {}
  
  Serial.println("Setting up MPU");
  bool setup_complete = setupMPU();
  //STOP PROGRAM OPERATIONS IF SETUP WAS NOT PROPERLY COMPLETED
  while(!setup_complete) {}
  
  Serial.println("Start data");
}

void loop() {
  printMPUVals("Accelerometer", accel_vals, 3);
  delay(1000);
}









bool setupMPU(){
  byte value;
  
  //CONFIGURATIONS
  Wire.beginTransmission(MPU);
  Wire.write(0x20);
  Wire.endTransmission();
  Wire.requestFrom(MPU, 1);
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

void printMPUVals(String data_name, const byte* data_addrs, int num_addrs) {
  byte results[num_addrs];
  int i;
  
  for(i = 0; i < num_addrs; i++)
    results[i] = 0x00;
  Serial.print(data_name);
  Serial.print(" values:\n{");
  getMPUValues(data_addrs, num_addrs, results, num_addrs);
  for(i = 0; i < num_addrs; i++) {
    Serial.print(results[i]);
    if(i < num_addrs - 1)
      Serial.print(", ");
  }
  Serial.println("}\n");
}

bool getMPUValues(const byte* registers, int num_registers, byte* results, int num_results) {
  bool result_ok;
  byte i,          //counter for register
        value,     //current value received from MPU
        byte_num,  //current byte number received from MPU
        current_num_results;  //total number of results received from MPU
  for(i = 0, result_ok = true, current_num_results = 0;
            i < num_registers && current_num_results < num_results; i++) {
    Wire.beginTransmission(MPU);
    Wire.write(registers[i]);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 2);
    
    byte_num = 0;
    value = 0;
    while(Wire.available())
      value += Wire.read() << (byte_num++ * 8);
    results[current_num_results++] = value;
    if(!value)
      result_ok = false;
  }
  
  return result_ok;
}
