#include <Servo.h>

Servo myservo;
int pos = 0;
int openPos = 0;
int closedPos = 53;
int chestSpeed = 75;
int signalPin = 4;
int chestStatus = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  pinMode(signalPin, INPUT_PULLUP);
  
  myservo.attach(9);
  SetChest(false);
}

void SetChest(boolean isOpen) {
  if(isOpen) {
    chestStatus = 1;
    for (pos = closedPos; pos > openPos; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(chestSpeed);                       // waits 15ms for the servo to reach the position
    }
  }
  else {
    chestStatus = 0;
    for(pos = openPos; pos <= closedPos; pos++) {
      myservo.write(pos);
      delay(chestSpeed);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    int _ = Serial.parseInt();
    SetChest(_ == 1);
  }

  int connectorVal = digitalRead(signalPin);
  
  Serial.println(connectorVal);
  delay(500);
  
  if(connectorVal == LOW && chestStatus != 1) {
    // Start opening (broken the connection)
    SetChest(true);
  }
}
