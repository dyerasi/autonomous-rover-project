#include <Servo.h>

Servo servo1;

int servoData = 9;
int echoPin = 6;
int trigPin = 5;

float distance;

int range;
int minDist;
int minAngle;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(servoData);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* 
  //test servo
  servo1.write(0);
  delay(1500);
  servo1.write(90);
  delay(1500);
  */
  /*
  float minDist = 900;
  int angle = 0;
  for(int k = 0; k <= 90; k++){
  servo1.write(k);
  delay(10);
  readDistance();
  if(minDist > distance){
    minDist = distance;
    angle = k;
  }
  }
    servo1.write(angle);
  Serial.println(distance);
  Serial.println(angle);
  delay(1000);
 */
 Serial.println(readDistance());
 delay(1000);
}

float readDistance(){
  // This function only works if the distance variable has been initialized and trigPin/echoPin
  // have been defined and set as outputs/inputs, respectively, using pinMode()
  
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Send out a pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // Turn trigPin off again
  digitalWrite(trigPin, LOW);
  // Calculate the distance
  distance = pulseIn(echoPin, HIGH)*0.0133/2;
  // Have the function return the floating point value of distance
  return distance;
}
