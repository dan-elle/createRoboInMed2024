#include <Servo.h>

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

int i = 0;
int clawButton = 2;

void setup() {
  //servo1.attach(3);
  //servo2.attach(4);
  Serial.begin(9600); 
  servo3.attach(6); 
 // servo4.attach(8); 
  pinMode (clawButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clawButton), openClaw, RISING);
  
}



void loop() {
   
}


void moveLeft(){
  Serial.print("left");
}

void moveRight(){
  Serial.print("right");
}

void moveUp(){
  Serial.print("up");
}

void moveDown(){
  Serial.print("down");
}

void openClaw(){
  i++;
  servo3.write(i);
}

void closeClaw(){
  Serial.print("close");
}
