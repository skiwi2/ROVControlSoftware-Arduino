#include <Servo.h>

//camera pins
static int SERVO_CX_PIN = 11;
static int SERVO_CY_PIN = 10;

//motor pins
static int MOTOR_LF_PIN = 3;
static int MOTOR_LB_PIN = 5;
static int MOTOR_RF_PIN = 6;
static int MOTOR_RB_PIN = 9;

Servo servoX;
Servo servoY;

int posY = 90;
int posX = 90;

void setup() {
  // put your setup code here, to run once:
  servoX.attach(SERVO_CX_PIN);
  servoY.attach(SERVO_CY_PIN);
  Serial.begin(9600);
  
  //set camera servos to default position
  servoX.write(posX);
  servoY.write(posY);
  
  //set motor pins to low
  digitalWrite(MOTOR_LF_PIN, LOW);
  digitalWrite(MOTOR_LB_PIN, LOW);
  digitalWrite(MOTOR_RF_PIN, LOW);
  digitalWrite(MOTOR_RB_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    String commandText = Serial.readStringUntil('\n');
    int spaceIndex = commandText.indexOf(' ');
    String command = commandText.substring(0, spaceIndex);
    String value = commandText.substring(spaceIndex, commandText.length());
    
    if (command == "cx") {
      servoX.write(180 - value.toInt());
    }
    else if (command == "cy") {
      servoY.write(180 - value.toInt());
    }
    else if (command == "ml") {
      setLeftMotor(value.toInt());
    }
    else if (command == "mr") {
      setRightMotor(value.toInt());
    }
    else {
      Serial.println("Unrecognized command: " + commandText);
    }
  }
}

void setLeftMotor(int value) {
  setMotor(value, MOTOR_LF_PIN, MOTOR_LB_PIN);
}

void setRightMotor(int value) {
  setMotor(value, MOTOR_RF_PIN, MOTOR_RB_PIN);
}

void setMotor(int value, int forwardPin, int backwardPin) {
  value = constrain(value, -10000, 10000);
  digitalWrite(forwardPin, LOW);
  digitalWrite(backwardPin, LOW);
  if (value < 0) {
    analogWrite(backwardPin, map(-value, 0, 10000, 0, 255));
  }
  else if (value > 0) {
    analogWrite(forwardPin, map(value, 0, 10000, 0, 255));
  }
}
