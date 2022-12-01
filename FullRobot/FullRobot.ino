
//Defines the pin for the Speed of the right motor
#define enA 3  

//Defines the pin for the Right Motor Forward 
#define in1 5  

//Defines the pin for the Right Motor Backward
#define in2 4  

//Defines the pin for the Left Motor Forward 
#define in3 10  

//Defines the pin for the Left Motor Backward
#define in4 9 

//Defines the pin for the Speed of the left motor 
#define enB 11  

//Defines the pin for the ir sensor Right
#define RightSensor 7  

//Defines the pin for the ir sensor Left
#define LeftSensor 8  

// All code inside of this method will run once at the beginning
void setup(){ 

    Serial.begin (9600) ;

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(RightSensor, INPUT); 

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(LeftSensor, INPUT); 

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(enA, OUTPUT); 

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(in1, OUTPUT); 

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(in2, OUTPUT);

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(in3, OUTPUT); 

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(in4, OUTPUT); 

    // This line sets the corresponding pin to either output or input depending on what its supposed to be
    pinMode(enB, OUTPUT);

    // as you can see, all of the sensor pins are input while the motor pins are output (lines 33 through 54)

    // This line turns on the motor pin that controls the speed, since it is a digital pin it can only turn on or off, thus on means the motor will be running at 100% power
    digitalWrite(enA, HIGH); 

    // This line turns on the motor pin that controls the speed, since it is a digital pin it can only turn on or off, thus on means the motor will be running at 100% power
    digitalWrite(enB, HIGH); 

    // This line simply waits for one second so you have time to let go of the robot before it starts moving
    delay(1000);

}

// This next method loops infinitely after the setup method and only stops when you turn the robot off
// its goal is to decide the state that the robot is in and act accordingly 
void loop(){ 

    // Each if statement in this method checks if a sensor detects a white line. If the the value of digitalRead(sensor) is 0 then it did not find the line

    bool sensingLeft = (digitalRead(LeftSensor) == 0);
    bool sensingRight = (digitalRead(RightSensor) == 0);
    Serial.print("Left Sensor reading: ");
    Serial.print(sensingLeft);
    Serial.print("   Right    ++Sensor reading: ");
    Serial.print(sensingRight);
    Serial.print("    ");

    if(sensingRight){

        if(sensingLeft){

            // This line only runs if both sensors detect something thus it means it reached its final destination and should stop
            Forward();
        }
        
        else{

            // This line only runs if only the right sensor detected anything thus it decides it is on the left side of the line and must turn right
            TurnRight();
            
        }
    }

    else{

        if(sensingLeft){
            // This line only runs if only the left sensor detected anything thus it decides it is on the right side of the line and must turn left
            TurnLeft();
        }
        else{
            // This line only runs if neither sensor detected anything thus it decides it must be on path and should continue to move forward/
            Stop();
        }
    }
}

// In order to move forward both motors have to move forward
void Forward(){  
    Serial.println("Going Forward");
    //Right Motor forward Pin 
    digitalWrite(in1, HIGH); 

    //Right Motor backward Pin eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
    digitalWrite(in2, LOW);  

    //Left Motor backward Pin 
    digitalWrite(in3, HIGH);  

    //Left Motor forward Pin 
    digitalWrite(in4, LOW);

}

// In order to turn right, the right motor must move backward and the left motor must move forward  
void TurnRight(){ 
    Serial.println("Turning Right");
    //Right Motor forward Pin 
    digitalWrite(in1, HIGH );  

    //Right Motor backward Pin  
    digitalWrite(in2, HIGH); 

    //Left Motor backward Pin 
    digitalWrite(in3, HIGH);  

    //Left Motor forward Pin 
    digitalWrite(in4, LOW); 

}


// In order to turn left, the right motor must move forward and the left motor must move backward  
void TurnLeft(){
    Serial.println("Turning Left");
    //Right Motor forward Pin 
    digitalWrite(in1, HIGH); 

    //Right Motor backward Pin 
    digitalWrite(in2, LOW);  

    //Left Motor backward Pin 
    digitalWrite(in3, LOW); 

    //Left Motor forward Pin 
    digitalWrite(in4, LOW);  

}

// In order to stop both motors must stop
void Stop(){
    Serial.println("Stopping");
    //Right Motor forward Pin 
    digitalWrite(in1, LOW); 

    //Right Motor backward Pin 
    digitalWrite(in2, LOW); 

    //Left Motor backward Pin 
    digitalWrite(in3, LOW); 

    //Left Motor forward Pin 
    digitalWrite(in4, LOW); 

}