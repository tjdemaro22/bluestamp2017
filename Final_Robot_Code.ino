//robot code

#include <SoftwareSerial.h> //Sotware Serial library, Set up XBee
SoftwareSerial xbee (2,3);

#include <Servo.h> //Servo library, Set up servos
Servo servoClaw;
Servo servoBase;

int dcL1Pin = 13; //Left DC motor information
int dcL2Pin = 12;
int dcLSpeedPin = 11; //PWM left DC motor
int dcR1Pin = 4; //Right DC motor information
int dcR2Pin = 5;
int dcRSpeedPin = 6; //PWM right DC motor

int servoClawPin = 9; //Claw servo information
int servoClawPos = 0;

int servoBasePin = 8; //Base servo information
int servoBasePos = 0;

char message = ' '; //Code from the glove

void setup() {
  xbee.begin(9600); //Switch on XBee
  Serial.begin(9600);
  
  pinMode(dcL1Pin,OUTPUT); //DC motor setup
  pinMode(dcL2Pin,OUTPUT);
  pinMode(dcLSpeedPin,OUTPUT);
  pinMode(dcR1Pin,OUTPUT);
  pinMode(dcR2Pin,OUTPUT);
  pinMode(dcRSpeedPin,OUTPUT);
  
  servoClaw.attach(servoClawPin); //Switch on servos
  servoBase.attach(servoBasePin);

  Serial.println("Program begun");
}

void loop() { //Note: code for DC motors uses PWM, and so the analogWrite's show (on a 0 to 255 scale) how often power is applied, and the digitalWrite's show to which wire connected to the motor (changing betweeen forward and backward)
  if (xbee.available()) {
    
    Serial.println("Xbee available"); //Display whether XBee network is working
    message = xbee.read(); //Read code from the glove's XBee
    
    if (message == 'A') { //Code for moving forward (both motors going forward)
      Serial.println("Forward");
      analogWrite(dcLSpeedPin, 255); //Motors on top speed
      digitalWrite(dcL1Pin, HIGH);
      digitalWrite(dcL2Pin, LOW);
      analogWrite(dcRSpeedPin, 255);
      digitalWrite(dcR1Pin, HIGH);
      digitalWrite(dcR2Pin, LOW);
    }
    
    if (message == 'B') { //Code for moving backward (both motors going backward)
      Serial.println("Backward");
      analogWrite(dcLSpeedPin, 255);
      digitalWrite(dcL1Pin, LOW);
      digitalWrite(dcL2Pin, HIGH);
      analogWrite(dcRSpeedPin, 255);
      digitalWrite(dcR1Pin, LOW);
      digitalWrite(dcR2Pin, HIGH);
    }
    
    if (message == 'C') { //Code for turning left tank-style (left motor forwards, right motor backwards)
      Serial.println("Turn Left");
      analogWrite(dcLSpeedPin, 255);
      digitalWrite(dcL1Pin, HIGH);
      digitalWrite(dcL2Pin, LOW);
      analogWrite(dcRSpeedPin, 255);
      digitalWrite(dcR1Pin, LOW);
      digitalWrite(dcR2Pin, HIGH);
    }
    
    if (message == 'D') { //Code for turning right tank-style (left motor backwards, right motor forwards)
      Serial.println("Turn Right");
      analogWrite(dcLSpeedPin, 255);
      digitalWrite(dcL1Pin, LOW);
      digitalWrite(dcL2Pin, HIGH);
      analogWrite(dcRSpeedPin, 255);
      digitalWrite(dcR1Pin, HIGH);
      digitalWrite(dcR2Pin, LOW);
    }
    
    if (message == 'E') { //Code for stopping (power cut from each motor)
      Serial.println("Stop");
      analogWrite(dcLSpeedPin, 0);
      digitalWrite(dcL1Pin, HIGH);
      digitalWrite(dcL2Pin, LOW);
      analogWrite(dcRSpeedPin, 0);
      digitalWrite(dcR1Pin, HIGH);
      digitalWrite(dcR2Pin, LOW);
    }
    
    if (message == 'F') { //Code to open the claw
      Serial.println("Claw Open");
      for (servoClawPos; servoClawPos < 163; servoClawPos += 1) {
      servoClaw.write(servoClawPos);
      delay(15);
      Serial.print("Claw servo is at ");
      Serial.println(servoClawPos);
      }
      Serial.println("The claw is open.");
    }
    
    if (message == 'G') { //Code to close the claw
      Serial.println("Claw Close");
      for (servoClawPos; servoClawPos > 10; servoClawPos -= 1) {
      servoClaw.write(servoClawPos);
      delay(15);
      Serial.print("Claw servo is at ");
      Serial.println(servoClawPos);
      }
      Serial.println("The claw is closed.");
    }
    
    if (message == 'H') { //Code to move the base forward
      Serial.println("Base Forward");
      for (servoBasePos; servoBasePos < 166; servoBasePos += 1) {
      servoBase.write(servoBasePos);
      delay(15);
      Serial.print("Base servo is at ");
      Serial.println(servoBasePos);
      delay(20);
      }
    }
    
    if (message == 'I') { //Code to move the base backward
      Serial.println("Base Backward");
      servoBasePos = 90;
      servoBase.write(servoBasePos);
      Serial.println("Base servo at 90");
    }
    
  }
}
