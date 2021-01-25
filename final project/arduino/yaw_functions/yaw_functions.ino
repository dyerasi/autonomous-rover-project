// This code is meant to find only the value of the yaw
// Similar code can easily be written in order to calculate pitch, roll, and x/y/z 
// acceleration, however, this should not be necessary

// MOSI = 51, MISO = 50, SCK = 52, CS = 53

// Get Gyroscope up and running
#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
float yaw = 0; 
float GyroZ, gyroAngleZ, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;


void setup()
{
  Serial.begin(19200);             
  Wire.begin(); // Initialize comunication
  Wire.beginTransmission(MPU); // Start communication 
  Wire.write(0x6B);  // Communicate with register 6B
  Wire.write(0x00); // Reset by placing a 0 into the 6B register
  Wire.endTransmission(true);
  calculate_IMU_error();
}

void loop()
{
  read_yaw();
  Serial.println(yaw);
}


float read_yaw() {
  previousTime = currentTime; // Use the time when read_yaw was last called as the previous time
  currentTime = millis(); // Update the value of the current time
  elapsedTime = (currentTime - previousTime) / 1000; // Find the elapsed time and divide by 1000 to get seconds

  Wire.beginTransmission(MPU); // Start Communication
  Wire.write(0x47); // Start with the first of the two registers that hold the GYRO_ZOUT data (There are GYRO_ZOUT_H and GYRO_ZOUT_L)
  Wire.endTransmission(false); // End the communication
  Wire.requestFrom(MPU, 2, true); // Read the values of the two bytes that contain the data we need
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0; // Combine the two bytes by left shifting the first 8 bits and adding on the second set of 8 bits
  // Correct the outputs with the calculated error values
  GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ ~ (-0.8)

  // Find the angle in degrees by multiplying the angular velocity, which is in deg/s, by time to get the change in angle and then add that to the initial angular position
  yaw =  yaw + GyroZ * elapsedTime;

  // Print the values on the serial monitor
  return yaw;
}


float calculate_IMU_error() {
  // Read gyro values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU); // Start communication
    Wire.write(0x47); // Start with the first of the two registers that hold the GYRO_ZOUT data (There are GYRO_ZOUT_H and GYRO_ZOUT_L)
    Wire.endTransmission(false); // End the communication
    Wire.requestFrom(MPU, 2, true); // Read the values of the two bytes that contain the data we need
    GyroZ = Wire.read() << 8 | Wire.read(); // Combine the two bytes by left shifting the first 8 bits and adding on the second set of 8 bits
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0); // Sum the average of the readings so that they can be averaged
    c++;
  }
  GyroErrorZ = GyroErrorZ / 200;  // Average the gyro readings so that we know what the 0 point is
  return GyroErrorZ;
}

