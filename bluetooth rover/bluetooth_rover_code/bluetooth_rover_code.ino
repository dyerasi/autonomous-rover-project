// Project #1 Example

// The purpose of this code is to provide an example outline of 
// code that achieves the goals of the first project

// Define the pins used to control the H bridge
/*
#define ENA 5
#define ENB 10
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
*/
#define ENA A0
#define ENB A1
#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10

// Define the pins used for the ultrasonic sensor
#define trigPin 6
#define echoPin 5

// Specify the speed (optional)
// This is only necessary if you choose to use analogWrite for ENA and ENB rather than digitalWrite
// You will notice that at around 120-140, your motors will not turn
// Because this is an analog output, the value of speed can be anything between 0 and 255
int speed = 255;
// Set up variable to dictate what motion should occur
char getstr;
char lastValid = ' ';
String lastPrinted = " ";

// Create global variable for distance, to be used when reading the ultrasonic
float distance;
//​
// Read the ultraonic sensor
float lookForward()
{
  // Ensure that the trigger pin is not sending out anything
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Activate the trigger pin for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Multiply time (in microseconds) by the speed of sound to get distance
  // Divide this by two because the pulse had to both go out to an object, and come back 
  //distance = pulseIn(echoPin, HIGH)*0.0133/2;​
  distance = pulseIn(echoPin, HIGH)*0.0133/2;
  // Return this distance value
  return distance;
}

// Functions for movement
void forward()
{
  // Print a message to the serial monitor saying that the rover
  // is moving forward
  if(lastPrinted != "Moving Forward"){
    Serial.println("Moving Forward");
    lastPrinted = "Moving Forward";
  }
  // Make all of the motors turn forwards
  analogWrite(ENA,speed); // Could also be digitalWrite(ENA, HIGH)
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  analogWrite(ENB,speed);
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,HIGH); 
}
//​
void backward() // You will need to fill in this function
{
  // Print a message to the serial monitor saying that the rover
  // is moving forward
  Serial.println("Moving Backward");
  lastPrinted = "Moving Backward";
  // Make all of the motors turn backwards
  analogWrite(ENA,speed); // Could also be digitalWrite(ENA, HIGH)
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);
  analogWrite(ENB,speed);
  digitalWrite(IN3,HIGH);  
  digitalWrite(IN4,LOW); 
}
//​
void right() // You will need to fill in this function
{
  // Print a message to the serial monitor saying that the rover
  // is moving forward
  Serial.println("Moving Right");
  lastPrinted = "Moving Right";
  // Make all of the motors turn right
 

analogWrite(ENA,speed); // Could also be digitalWrite(ENA, HIGH)
  //digitalWrite(IN1,LOW); 
  digitalWrite(IN2,LOW);
  digitalWrite(IN1, HIGH);

    analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
 // analogWrite(ENB, speed);
}
//​
void left() // You will need to fill in this function
{
  // Print a message to the serial monitor saying that the rover
  // is moving forward
  Serial.println("Moving Left");
  lastPrinted = "Moving Left";
  // Make all of the motors turn left
  analogWrite(ENA,speed); // Could also be digitalWrite(ENA, HIGH)
  //digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  digitalWrite(IN1, LOW);

    analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 // analogWrite(ENB, speed);
}
//​

void stop() 
{
  // Print a message to the serial monitor saying that the rover has stopped
  Serial.println("Stopped");
  lastPrinted = "Stopped";
  // Switch ENA and ENB to low so that all motors stop turning
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}

void setup()
{
  // Define the pins controlling the motors as outputs
  pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT); pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT); pinMode(ENB,OUTPUT);

  // Set the trig pin as an output and the echo pin as an input
  pinMode(trigPin,OUTPUT); pinMode(echoPin,INPUT);
  
  // Begin serial communication
  Serial.begin(9600); 
}
void loop()
{
  // Read the value from the serial monitor
  getstr = Serial.read();
  if (getstr == 'f'){ 
    lastValid = 'f';
    float d = lookForward();
    if(d < 8){
      stop();
      if(lastPrinted != "Stopped"){
        Serial.println("Object within 6inch range, rover stopping");
        //lastPrinted = "Object within 6inch range, rover stopping";
      }
    }
    else{
      forward();
      }
    }
  // If the letter 'b' is received, go backwards
  else if (getstr == 'b'){
    lastValid = 'b';
    backward();
  }
  // If the letter 'l' is received, turn left
  else if (getstr == 'l'){
    lastValid = 'l';
    left();
  }
  // If the letter 'r' is received, turn right
  else if (getstr == 'r'){
    lastValid = 'r';
    right();
  }
  // If the letter 's' is received, stop
  else if (getstr == 's'){
    lastValid = 's';
    stop();
  }
  else if (getstr == 'd'){ 
    lookForward();
    delay(1000);
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  else if (lastValid == 'f'){
    lastValid = 'f';
    float d = lookForward();
    if(d < 8){
      Serial.println("Object within 6inch range, rover stopping");
      stop();
    }
    else{
      forward();
      }
  }
}
