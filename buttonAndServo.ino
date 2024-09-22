#include <Servo.h>

#define BUTTON_PIN1 3
#define BUTTON_PIN2 2

volatile bool buttonPress1 = false;
volatile bool buttonPress2 = false;

Servo servo1;
int servo1Pos = 0;

void buttonPinInterrupt1(){
  buttonPress1 = !buttonPress1;
}

void buttonPinInterrupt2(){
  buttonPress2 = !buttonPress2;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  servo1.attach(13);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN1),
                  buttonPinInterrupt1,
                  CHANGE);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN2), buttonPinInterrupt2, CHANGE);
}

void loop() {
  while (buttonPress1) {
    servo1Pos++;
    servo1.write(servo1Pos);
    Serial.println("press1");
  }
  while (buttonPress2) {
    servo1Pos--;
    servo1.write(servo1Pos);
    Serial.println("press2");
  }
}
