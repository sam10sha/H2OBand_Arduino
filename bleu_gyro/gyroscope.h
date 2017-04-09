/// Sets up the gyroscope
void gyroscope_setup();

/// Prints out the values from the accelerometer, magnetometer, gyroscope, and temperature sensor
void gyroscope_operate();

/// Retrieves the values for the accelerometer, magnetometer, gyroscope, and temperature sensor
/// @param accel_vals  The storage location for the accelerometer values
/// @param mag_vals    The storage location for the magnetometer values
/// @param gyro_vals   The storage location for the gyroscope values
/// @param temp        The storage location for the temperature sensor value
void gyroscope_retrieve_values(int accel_vals[3], int mag_vals[3], int gyro_vals[3], int* temp);
