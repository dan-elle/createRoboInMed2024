#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);       // called this way, it uses the default address 0x40   


#define SERVOMIN  125                                                 // this is the 'minimum' pulse length count (out of 4096)

#define SERVOMAX  625                                                 // this is the 'maximum' pulse length count (out of 4096)

//Keep track of which pins are being used for buttons
#define BUTTON_PIN1 3
#define BUTTON_PIN2 2
#define BUTTON_PIN3 18

//Keep track of buttons being ACTIVELY pressed down
volatile bool buttonPress1 = false;
volatile bool buttonPress2 = false;

int servo1Pos = 0; //current servo position
int currentServo = 0; //which motor is being moved

//Also to keep track of buttons ACTIVELY being pressed down
void buttonPinInterrupt1(){
  buttonPress1 = !buttonPress1;
}

//Also to keep track of buttons ACTIVELY being pressed down
void buttonPinInterrupt2(){
  buttonPress2 = !buttonPress2;
}

//To flip between the different servos
void buttonPinInterrupt3(){
  //There are only 3 motors
  if (currentServo == 3){
    currentServo = 0;
  }
  else{
    currentServo++;
  }
  Serial.println(currentServo);
}

void setup() {
  //Standard set up stuff
  Serial.begin(9600);
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  
  //Give each button a function
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN1), buttonPinInterrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN2), buttonPinInterrupt2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN3), buttonPinInterrupt3, RISING);

  //Create the board
  board1.begin();
  board1.setPWMFreq(60);                  // Analog servos run at ~60 Hz updates

}

void loop() {
  //Increase angle
  while (buttonPress1 && servo1Pos<181) {
    servo1Pos += 10;
    board1.setPWM(currentServo, 0, angleToPulse(servo1Pos) );
    Serial.println("press1");
  }
  //Decrease angle
  while (buttonPress2 && servo1Pos>0) {
    servo1Pos -= 10;
    board1.setPWM(currentServo, 0, angleToPulse(servo1Pos) );
    Serial.println("press2");
  }
}

int angleToPulse(int ang)                             //gets angle in degree and returns the pulse width

  {  int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max 
     Serial.print("Angle: ");Serial.print(ang);
     Serial.print(" pulse: ");Serial.println(pulse);
     return pulse;
  }
