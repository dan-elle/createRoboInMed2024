int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;
int led5 = 9;
int led6 = 8;

int ledState = LOW;
int x;
int xDoubled;
void setup() {
  Serial.begin (9600);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led4, OUTPUT);
  pinMode (led5, OUTPUT);
  pinMode (led6, OUTPUT);

}

void loop() {
  x = analogRead(A0);
  xDoubled = x*2;
  if (xDoubled <= 170){
    digitalWrite(led6,HIGH);
    delay (20000);
    digitalWrite(led6,LOW);
  }
  if (300>xDoubled<690) {
    digitalWrite (led4, HIGH);
    digitalWrite (led3, HIGH);
    delay (20000);
    digitalWrite (led4, LOW);
    digitalWrite (led3, LOW);
  }
  if (750 > xDoubled < 860){
    digitalWrite(led2, HIGH);
    delay(20000);
    digitalWrite(led2,LOW);
  }
  if(xDoubled >900){
    digitalWrite (led1, HIGH);
    delay (20000);
    digitalWrite(led1,LOW);
  }

}
