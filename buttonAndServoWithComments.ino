#include <Servo.h>

#include <Adafruit_PWMServoDriver.h>


#define SERVOMIN  125                                                 // this is the 'minimum' pulse length count (out of 4096)

#define SERVOMAX  625                                                 // this is the 'maximum' pulse length count (out of 4096)
#define BUTTON_PIN1 3
#define BUTTON_PIN2 2

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);       // called this way, it uses the default address 0x40


//These are flags. they help us keep track of what the servos should be doing.
volatile bool buttonPress1 = false;
volatile bool buttonPress2 = false;

Servo servo1;
int servo1Pos = 0; //keeping track of how much the servo has turned

//These are your interrupt programs!
//The way this code works is by using interrupts to change the flags we created earlier
//whenever a button is pressed or released.
void buttonPinInterrupt1(){
  buttonPress1 = !buttonPress1;
}

void buttonPinInterrupt2(){
  buttonPress2 = !buttonPress2;
}

void setup() {
  //Set up the communication with the Arduino
  Serial.begin(9600);
  
  //Tell the Arduino where the buttons are and that they will give input
  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);

  board1.begin();
  board1.setPWMFreq(60);                  // Analog servos run at ~60 Hz updates

  //Add the connections between the button pins and the interrupt functions
  //Here we tell the board that if there is any CHANGE (button is pressed OR released),
  //then we should stop what we're doing to run the interrupt program
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN1), buttonPinInterrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN2), buttonPinInterrupt2, CHANGE);
}

void loop() {
  //Now we use the flags we created!

  while (buttonPress1) { //As long as the button is pressed do the things below
    if (servo1Pos<181){
      servo1Pos++; //increase the servo angle
      board1.setPWM(0, 0, angleToPulse(servo1Pos)); //send the new angle to the servo
    }
    Serial.println("press1"); //this just prints a statement to Serial monitor (under tools) for testing
  }
  while (buttonPress2) {
    if (servo1Pos>0){
      servo1Pos--; //increase the servo angle
      board1.setPWM(0, 0, angleToPulse(servo1Pos)); //send the new angle to the servo
    }
    Serial.println("press2"); //this just prints a statement to Serial monitor (under tools) for testing 
  }
}

int angleToPulse(int ang)                             //gets angle in degree and returns the pulse width
  {  int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
     Serial.print("Angle: ");
     Serial.print(ang);
     Serial.print(" pulse: ");
     Serial.println(pulse);
     return pulse;

  }
