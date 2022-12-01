
// ---------------------------------------------------------------- // 
// Arduino Origami Bot 
// Created by USF Department of Engineering
// Using Arduino IDE 1.8.19
// Tested Oct. 4 
// ---------------------------------------------------------------- // 

#include <LiquidCrystal_I2C.h> // liquid crystal library
#include <Wire.h>
#include<stdlib.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // specifices how to refrence the LCD and it's characteristics


// define varibales

char array1[] = "Robot State:    ";
char array2[] = "STOPPED         ";
char array3[] = "BACKWARD        ";
char array4[] = "FORWARD         ";
char array5[] = "OUT OF RANGE    ";

int echoPin = 8; // attach pin D8 to pin Echo of HC-SR04
int trigPin = 7; // attach pin D7 to pin Trig of HC-SR04
int in1 = 5; // variable names for the L298N
int in2 = 4; // variable names for the L298N
int in3 = 10; // variable names for the L298N
int in4 = 9; // variable names for the +L298N
int ena = 3;
int enb = 11;

int LCDprev = 99; // helps to update the LCD state tracks previous
int LCDcurr = 100; // helps to update the LCD state tracks current

int ledpin = 13; //specify the LED pin to pin 13

int distance; // distance measurement

#define accuracy 5

int distances[accuracy];

int getDistanceNow(){
  digitalWrite (trigPin, LOW);//starts trig pin low
  delayMicroseconds (2); //waits for hardware to respond
  digitalWrite (trigPin, HIGH); //makes trig pin high
  delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
  digitalWrite (trigPin, LOW); //after 10 microseconds trig pin is brought low
  long duration = pulseIn (echoPin, HIGH); //reads echo as it receives the pulse and stores duration
  int dist = duration * 0.034 / 2; // Converts the time of flight to distance to object

  // Displays the distance on the serial Monitor
  return dist;
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

//yes I know remaking an ordered array can get costly but frankly it doesn't matter right now so no point in micro optimizing
int getDistance(){
  
  for(int i = 0; i < accuracy-1; i++){
    distances[i] = distances[i+1];
  }
  distances[accuracy - 1] = getDistanceNow();

  int orderedDistances[accuracy];

  for(int i = 0; i < accuracy; i++){
    orderedDistances[i] = distances[i];
  }
  qsort(orderedDistances, accuracy, sizeof(int), compare);
  Serial.print ("Distance: ");
  Serial.print (orderedDistances[accuracy/2]);
  Serial.println(" cm");
  return orderedDistances[accuracy/2];
}

void setup() {
  lcd.init(); // initializes LCD
  lcd.backlight(); // turn on backlight

  pinMode (trigPin, OUTPUT) ; // sonar digital pin mode for trig
  pinMode (echoPin, INPUT); // sonar digital pin mode for echo
  
  pinMode (in1, OUTPUT); // all L298N digital pins are outputs
  pinMode (in2, OUTPUT); // all L298N digital pins are outputs
  pinMode (in3, OUTPUT); // all L298N digital pins are outputs
  pinMode (in4, OUTPUT); // all L298N digital pins are outputs
  pinMode (ledpin, OUTPUT) ; // configure LCD pin as an output
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  analogWrite(ena, 255); //ENA pin
  analogWrite(enb , 255); //ENB pin

  Serial.begin (9600) ; // use default of 9600 baud rate for serial communication

  lcd.setCursor(0, 0); // set cursor at top left
//  lcd.print("TEST");

  lcd.print (array1); //prints the first line "Robot State:
  for(int i = 0; i < accuracy; i++){
    distances[i] = getDistanceNow();
  }
  
}


void loop() {
  
/*  
  NOTE: it is important only to update the LCD screen when a change of state has occured
  Otherwise, the program become inefficient. We only want to write to the LCD when 
  there is a change in what the robot is doing. The LCDprey and LCDcurr variables 
   help us to do this
*/
  LCDprev = LCDcurr;

  distance = getDistance();
  if (distance <= 15) {
    LCDcurr = 1;

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(ledpin, HIGH);

    if (LCDprev != LCDcurr) {
      lcd.setCursor(0, 1);
      lcd.print(array3);
      delay(10);
    }
    
  } else if (distance <= 30) {
    LCDcurr = 2;

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(ledpin, LOW);

    if (LCDprev != LCDcurr) {
      lcd.setCursor(0, 1);
      lcd.print(array2);
      delay(10);
    }
    
  } else if (distance <= 45) {
    LCDcurr = 3;

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(ledpin, HIGH);

    if (LCDprev != LCDcurr) {
      lcd.setCursor(0, 1);
      lcd.print(array4);
      delay(10);
    }
    
  } else {
    LCDcurr = 4;

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(ledpin, LOW);

    if (LCDprev != LCDcurr) {
      lcd.setCursor(0, 1);
      lcd.print(array5);
      delay(10);
    }
    
  }
  delay(10);
  
}
