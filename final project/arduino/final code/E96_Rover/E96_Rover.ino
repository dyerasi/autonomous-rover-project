// Define the pins used to control the H bridges
#define ENA A15
#define ENB A14
#define IN1 47
#define IN2 49
#define IN3 51
#define IN4 53

#define ENC A12
#define END A13
#define IN5 23
#define IN6 25
#define IN7 27
#define IN8 29

// Define pins used to control sensors
#define FRTRIG 32
#define FRECHO 34
#define FLTRIG 28
#define FLECHO 30
#define LTRIG 24
#define LECHO 26
#define RTRIG 52
#define RECHO 50
#define BLTRIG 13
#define BLECHO 12
#define BRTRIG 10
#define BRECHO 11

float distance;
float desired_yaw = 0;

// Get Gyroscope up and running
#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
float yaw = 0; 
float GyroZ, gyroAngleZ, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;
float momentum_error = 4; 
// Specify the speed (optional)
// This is only necessary if you choose to use analogWrite for ENA and ENB rather than digitalWrite
// You will notice that at around 120-140, your motors will not turn
// Because this is an analog output, the value of speed can be anything between 0 and 255
int speed = 200;

// Set up variable to dictate what motion should occur
char getstr;

void setupMotors()
{
  // Define the pins controlling the motors as outputs
  /*
   input 1 is LOW and input 2 is HIGH the motor will move forward, and vice versa, 
   if input 1 is HIGH and input 2 is LOW the motor will move backward. 
   In case both inputs are same, either LOW or HIGH the motor will stop.
  */
  pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT); pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT); pinMode(ENB,OUTPUT);

  pinMode(IN5, OUTPUT); pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT); pinMode(IN8, OUTPUT);
  pinMode(ENC, OUTPUT); pinMode(END, OUTPUT);
}

void setupSensors()
{
  pinMode (FRTRIG, OUTPUT);
  pinMode (FRECHO, INPUT);
  pinMode (FLTRIG, OUTPUT);
  pinMode (FLECHO, INPUT);
  pinMode (RTRIG, OUTPUT);
  pinMode (RECHO, INPUT);
  pinMode (LTRIG, OUTPUT);
  pinMode (LECHO, INPUT);
  pinMode (BRTRIG, OUTPUT);
  pinMode (BRECHO, INPUT);
  pinMode (BLTRIG, OUTPUT);
  pinMode (BLECHO, INPUT);
}

void setupGyro()
{
  Serial.begin(19200);             
  Wire.begin(); // Initialize comunication
  Wire.beginTransmission(MPU); // Start communication 
  Wire.write(0x6B);  // Communicate with register 6B
  Wire.write(0x00); // Reset by placing a 0 into the 6B register
  Wire.endTransmission(true);
  calculate_IMU_error();
  smart_delay(200);
}

void setup()
{
  delay(1500);
  setupMotors();
  setupGyro();
  setupSensors();
  smart_delay(1000);
}
/*
 * desired_yaw = 0, 90, or -90
 * change desired_yaw
 * call left then while(..) with read_yawe
 * if read_yaw is slightly off
 *  fix yaw going other way
 */

void smart_delay(unsigned long delay_time){ // This function delays code execution for a set amount of time, while reading the gyroscope;
  unsigned long ctime = millis();
  while ( (unsigned long)(millis() - ctime) < delay_time){
    read_yaw();
    delayMicroseconds(20);
  }
}

void loop()
{
  smart_delay(1000);
  leftDegree();
  smart_delay(1000);
  rightDegree();
 // navigate_obstacles();
}

void rightDegree()
{
  desired_yaw = desired_yaw+90;
  //float temp = read_yaw();
    read_yaw();
  smart_delay(200);
  Serial.println(read_yaw());
  Serial.println(desired_yaw);
  right();
  while (yaw <= (desired_yaw)){
    //smart_delay(10);
    //temp = read_yaw();
    //smart_delay(10);
    read_yaw();
  }
  stop_movement();
  smart_delay(20);
  /*
  float error = read_yaw() - d;
  if(abs(error) > 3){
    leftDegree(abs(error));
  }
  */
}

void leftDegree()
{
  desired_yaw = desired_yaw-90;
  //float temp = read_yaw();
  read_yaw();
  smart_delay(200);
      left();
  while (yaw >= (desired_yaw)){
    read_yaw();
    //smart_delay(10);
    //temp = read_yaw();
    //Serial.println(temp);
    //smart_delay(10);
  }
  stop_movement();
  smart_delay(20);
  /*
  float error = read_yaw() + d;
  if(abs(error) > 3){
    rightDegree(abs(error));
  }
  */
}

// Functions for movement
void forward()
{
  Serial.println("Moving Forward");

  // Make all of the motors turn forwards

  // FRONT LEFT FORWARD
  analogWrite(ENC, speed);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);

  // FRONT RIGHT FORWARD
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // BACK LEFT FORWARD
  analogWrite(END, speed);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);

  // BACK RIGHT FORWARD
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  read_yaw();
}
//​
void backward() // You will need to fill in this function
{

  Serial.println("Moving Backward");
  
  // FRONT LEFT BACKWARD
  analogWrite(ENC, speed);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);

  // FRONT RIGHT BACKWARD
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // BACK LEFT BACKWARD
  analogWrite(END, speed);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);

  // BACK RIGHT BACKWARD
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  read_yaw();
}
//​
void right() // You wisll need to fill in this function
{
  Serial.println("Moving Right");
 
  // FRONT LEFT FORWARD
  analogWrite(ENC, speed);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);

  // FRONT RIGHT BACKWARD
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // BACK LEFT FORWARD
  analogWrite(END, speed);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);

  // BACK RIGHT BACKWARD
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  read_yaw();
}


void left() // You will need to fill in this function
{
  
  Serial.println("Moving Left");

  // FRONT LEFT BACKWARD
  analogWrite(ENC, speed);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);

  // FRONT RIGHT FORWARD
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // BACK LEFT BACKWARD
  analogWrite(END, speed);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);

  // BACK RIGHT FORWARD
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  read_yaw();
}

void stop_movement() 
{
  Serial.println("Stopped");

  // Switch ENA and ENB to low so that all motors stop turning
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
  analogWrite(ENC, LOW);
  analogWrite(END, LOW);

  read_yaw();
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

bool checkDistance(float temp){
  if(temp > 700 || temp==0)
    return false;
  return true;
}

float readFrontLeftDistance()
{
  read_yaw();
  digitalWrite(FLTRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(FLTRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(FLTRIG, LOW);
  float temp = pulseIn(FLECHO, HIGH)*0.0133/2;
  if(checkDistance(temp))
    return temp;
  return readFrontLeftDistance();
}

float readFrontRightDistance()
{
  read_yaw();
  digitalWrite(FRTRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(FRTRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRTRIG, LOW);
  float temp = pulseIn(FRECHO, HIGH)*0.0133/2;
  if(checkDistance(temp))
    return temp;
  return readFrontRightDistance();
}

float readFrontDistance()
{
  read_yaw();
  Serial.println(min(readFrontLeftDistance(), readFrontRightDistance())); //testing purposes
  return min(readFrontLeftDistance(), readFrontRightDistance());
}

float readBackLeftDistance()
{
  read_yaw();
  digitalWrite(BLTRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(BLTRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(BLTRIG, LOW);
  float temp = pulseIn(BLECHO, HIGH)*0.0133/2;
  if(checkDistance(temp))
    return temp;
  return readBackLeftDistance();
}

float readFrontDistanceOverTime(){
  float sum = 0.0;
  for(int i = 0; i != 10; i++){
    sum += readFrontDistance();
    smart_delay(10);
  }
  return sum/10.;
  
}

float readBackRightDistance()
{
  digitalWrite(BRTRIG, LOW);
  smart_delay(2);
  digitalWrite(BRTRIG, HIGH);
  smart_delay(10);
  digitalWrite(BRTRIG, LOW);
  float temp = pulseIn(BRECHO, HIGH)*0.0133/2;
  if(checkDistance(temp))
    return temp;
  return readBackRightDistance();
}

float readBackDistance()
{
  return min(readBackLeftDistance(), readBackRightDistance());
}

float readLeftDistance()
{
  digitalWrite(LTRIG, LOW);
  smart_delay(2);

  digitalWrite(LTRIG, HIGH);
  smart_delay(10);

  digitalWrite(LTRIG, LOW);

  float temp = pulseIn(LECHO, HIGH)*0.0133/2; 
  if(checkDistance(temp))
    return temp;
  return readLeftDistance();
}

float readRightDistance()
{
  digitalWrite(RTRIG, LOW);
  smart_delay(2);

  digitalWrite(RTRIG, HIGH);
  smart_delay(10);

  digitalWrite(RTRIG, LOW);

  float temp = pulseIn(RECHO, HIGH)*0.0133/2; 
  if(checkDistance(temp))
    return temp;
  return readRightDistance();
}



void navigate_obstacles(){
  float ld = 0;
  float rd = 0;
  forward();
  while(readFrontDistanceOverTime() > 8){
    smart_delay(10);
  }
  stop_movement();
  smart_delay(100);
  ld = readLeftDistance();
  rd = readRightDistance();
  if(ld > rd){
    leftDegree();
    smart_delay(1000);
    forward();
    while(readFrontDistanceOverTime() > 8 && readRightDistance() < 10){
      smart_delay(10);
    }
    stop_movement();
        smart_delay(200);
    rightDegree();
  }
  else{
    rightDegree();
    smart_delay(1000);
    forward();
    while(readFrontDistanceOverTime() > 8 && readLeftDistance() < 10){
      smart_delay(10);
    }
    stop_movement();
    smart_delay(200);
    leftDegree();
  }

  delay(2000); //testing purposes
}
