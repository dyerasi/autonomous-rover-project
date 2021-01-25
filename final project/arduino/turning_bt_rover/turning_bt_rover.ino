// Project #1 Example

// Define the pins used to control the H bridge

#define ENA A0
#define ENB A1
#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10

#define ENC A2
#define END A3
#define IN5 7
#define IN6 6
#define IN7 5
#define IN8 4
 
// Specify the speed (optional)
// This is only necessary if you choose to use analogWrite for ENA and ENB rather than digitalWrite
// You will notice that at around 120-140, your motors will not turn
// Because this is an analog output, the value of speed can be anything between 0 and 255
int speed = 255;

// Set up variable to dictate what motion should occur
char getstr;


void setup()
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
void loop()
{
  // Read the value from the serial monitor
  getstr = 'r';

  
  switch(getstr){
    case 'f':
      forward();
      break;
    case 'b':
      backward();
      break;
    case 'l':
      left();
      break;
    case 'r':
      right();
      break;
    case 's':
      stop();
      break;
    default:
      Serial.println("Error in Input");
  }
  

}

// Functions for movement
void forward()
{
  Serial.println("Moving Forward");

  // Make all of the motors turn forwards

  //forward left wheel
  analogWrite(ENA,speed); 
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);

  
  //backward left wheel
  analogWrite(ENC,speed); 
  digitalWrite(IN5,LOW); 
  digitalWrite(IN6,HIGH);
  
  
  //forward right wheel
  analogWrite(ENB,speed);
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,HIGH); 

  
  //backward right wheel
  analogWrite(END,speed); 
  digitalWrite(IN7,LOW); 
  digitalWrite(IN8,HIGH);
  
}
//​
void backward() // You will need to fill in this function
{

  Serial.println("Moving Backward");
  
  //forward left wheel
  analogWrite(ENA,speed); 
  digitalWrite(IN1,HIGH); 
  digitalWrite(IN2,LOW);

  //backward left wheel
  analogWrite(ENC,speed); 
  digitalWrite(IN5,HIGH); 
  digitalWrite(IN6,LOW);

  //forward right wheel
  analogWrite(ENB,speed);
  digitalWrite(IN3,HIGH);  
  digitalWrite(IN4,LOW); 

  //backward right wheel
  analogWrite(END,speed); 
  digitalWrite(IN7,HIGH); 
  digitalWrite(IN8,LOW); 
}
//​
void right() // You wisll need to fill in this function
{
  Serial.println("Moving Right");
 
  //forward left wheel
  analogWrite(ENA,speed); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2,LOW);

  //backward left wheel
  analogWrite(ENC,speed); 
  digitalWrite(IN5,HIGH); 
  digitalWrite(IN6,LOW);

  //forward right wheel
  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //backward right wheel
  analogWrite(END,speed); 
  digitalWrite(IN7,LOW); 
  digitalWrite(IN8,HIGH);
}


void left() // You will need to fill in this function
{
  
  Serial.println("Moving Left");

  //forward left wheel
  analogWrite(ENA,speed); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2,HIGH);

  //backward left wheel
  analogWrite(ENC,speed); 
  digitalWrite(IN5, LOW); 
  digitalWrite(IN6, HIGH);

  //forward right wheels
  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  //backward right wheel
  analogWrite(END,speed); 
  digitalWrite(IN7,HIGH); 
  digitalWrite(IN8,LOW);
}


void stop() 
{
  Serial.println("Stopped");

  // Switch ENA and ENB to low so that all motors stop turning
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
}
