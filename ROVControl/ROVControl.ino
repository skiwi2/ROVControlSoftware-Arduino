#include <Servo.h>

Servo servoX;
Servo servoY;

int posY = 90;
int posX = 90;

void setup() {
  // put your setup code here, to run once:
  servoX.attach(11);
  servoY.attach(10);
  Serial.begin(9600);
  servoX.write(posX);
  servoY.write(posY);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    int spaceIndex = command.indexOf(' ');
    String xy = command.substring(0, spaceIndex);
    String amount = command.substring(spaceIndex, command.length());
    int amountInt = amount.toInt();
    
    if (xy == "x") {
      servoX.write(amountInt);
    }
    else if (xy == "y") {
      servoY.write(amountInt);
    }
    else {
      Serial.println("Unrecognized command: " + command);
    }
  }
}
