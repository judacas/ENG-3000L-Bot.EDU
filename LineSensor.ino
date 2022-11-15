// Arduino Line Follower Robot Code

#define R_S 4//ir sensor Right

#define L_S 2 //ir sensor Left

void setup(){ 

pinMode(Rs, INPUT); 

pinMode(Ls, INPUT);  


}

void loop(){  

if((digitalRead(Rs) == 0)&&(digitalRead(Ls) == 0)){forward();}   //if Right Sensor and Left Sensor are at White color then it will call forword function

if((digitalRead(Rs) == 1)&&(digitalRead(Ls) == 0)){turnRight();} //if Right Sensor is Black and Left Sensor is White then it will call turn Right function  

if((digitalRead(Rs) == 0)&&(digitalRead(Ls) == 1)){turnLeft();}  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function

if((digitalRead(Rs) == 1)&&(digitalRead(Ls) == 1)){Stop();} //if Right Sensor and Left Sensor are at Black color then it will call Stop function

}
