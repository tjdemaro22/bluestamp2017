//glove code

#include <SoftwareSerial.h> //Software Serial library, Set up XBee
SoftwareSerial xbee(2, 3);

int flexOne = 0; //Sensor readings
int flexTwo = 0;
int flexThree = 0;
int flexFour = 0;
int flexFive = 0;

int flexOneMap = 0; //Mapped readings (1 to 100 scale)
int lfexTwoMap = 0;
int flexThreeMap = 0;
int flexFourMap = 0;
int flexFiveMap = 0;

int flexOneMapLength = 0; //Length of mapped digits (only three are necessary)
int flexTwoMapLength = 0;
int flexThreeMapLength = 0;
int flexFourMapLength = 0;

void setup() {
  xbee.begin(9600); //Switch on the xbee
  Serial.begin(9600);
  
  Serial.println("Program begun");
}

void loop() {
  int flexOne = analogRead(A1); //Read the sensors
  int flexTwo = analogRead(A2);
  int flexThree = analogRead(A3);
  int flexFour = analogRead(A4);
  int flexFive = analogRead(A5);
  
  int flexOneMap = map(flexOne, 410, 525, 100, 0); //Map the sensor values
  int flexTwoMap = map(flexTwo, 363, 488, 100, 0);
  int flexThreeMap = map(flexThree, 342, 532, 100, 0);
  int flexFourMap = map(flexFour, 433, 574, 100, 0);
  int flexFiveMap = map(flexFive, 356, 555, 100, 0); 
  
  if (flexOneMap >= 100) //Determine the length of mapped values one through four
    int flexOneMapLength = 3;
  else
    int flexOneMapLength = 2;
    
  if (flexTwoMap >= 100)
    int flexTwoMapLength = 3;
  else
    int flexTwoMapLength = 2;
    
  if (flexThreeMap >= 100)
    int flexThreeMapLength = 3;
  else
    int flexThreeMapLength = 2;

  if (flexFourMap >= 100)
    int flexFourMapLength = 3;
  else
    int flexFourMapLength = 2;
    
  Serial.print(flexOneMap); //Report all mapped values to the monitor
  if (flexOneMapLength == 2)
    Serial.print("   ");
  else
    Serial.print("  ");
    
  Serial.print(flexTwoMap);
  if (flexTwoMapLength == 2)
    Serial.print("   ");
  else
    Serial.print("  ");
    
  Serial.print(flexThreeMap);
  if (flexThreeMapLength == 2)
    Serial.print("   ");
  else
    Serial.print("  ");
    
  Serial.print(flexFourMap);
  if (flexFourMapLength == 2)
    Serial.print("   ");
  else
    Serial.print("  ");
    
  Serial.println(flexFiveMap);
  delay(500);

  if (flexOneMap >= 50 && flexTwoMap >= 50 && flexThreeMap >= 50 && flexFourMap >= 50 && flexFiveMap >= 50) { //All fingers closed
    xbee.write('A'); //Send code to the robot's XBee
    Serial.println("Sending A; Forward");
  }
  if (flexOneMap >= 50 && flexTwoMap >= 50 && flexThreeMap >= 50 && flexFourMap >= 50 && flexFiveMap <= 50) { //Fifth finger open and others closed
    xbee.write('B');
    Serial.println("Sending B; Backward");
  }
  if (flexOneMap >= 50 && flexTwoMap >= 50 && flexThreeMap <= 50 && flexFourMap <= 50 && flexFiveMap <= 50) { //Thumb and index fingers closed and others open
    xbee.write('C');
    Serial.println("Sending C; Turn Left");
  }
  if (flexOneMap <= 50 && flexTwoMap <= 50 && flexThreeMap <= 50 && flexFourMap >= 50 && flexFiveMap >= 50) { //Ring and fifth fingers closed adn others open
    xbee.write('D');
    Serial.println("Sending D; Turn Right");
  }
  if (flexOneMap <= 50 && flexTwoMap <= 50 && flexThreeMap <= 50 && flexFourMap <= 50 && flexFiveMap <= 50) { //All fingers open
    xbee.write('E');
    Serial.println("Sending E; Stop");
  }
  if (flexOneMap <= 50 && flexTwoMap <= 50 && flexThreeMap >= 50 && flexFourMap >= 50 && flexFiveMap <= 50) { //Middle and ring fingers closed and others open
    xbee.write('F');
    Serial.println("Sending F; Claw Open");
  }
  if (flexOneMap >= 50 && flexTwoMap >= 50 && flexThreeMap <= 50 && flexFourMap <= 50 && flexFiveMap >= 50) { //Middle and ring fingers open and others closed
    xbee.write('G');
    Serial.println("Sending G; Claw close");
  }
  if (flexOneMap >= 50 && flexTwoMap <= 50 && flexThreeMap <= 50 && flexFourMap <= 50 && flexFiveMap <= 50) { //Thumb open and others closed
    xbee.write('H');
    Serial.println("Sending H; Base Forward");
  }
  if (flexOneMap <= 50 && flexTwoMap >= 50 && flexThreeMap <= 50 && flexFourMap <= 50 && flexFiveMap <= 50) { //Index finger open and others closed
    xbee.write('I');
    Serial.println("Sending I; Base Backward");
  }
}
