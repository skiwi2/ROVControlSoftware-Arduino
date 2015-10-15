#include <Servo.h>

//camera pins
static int SERVO_CX_PIN = 11;
static int SERVO_CY_PIN = 10;

//shovel pins
static int SERVO_SX_PIN = 13;

//motor pins
static int MOTOR_LF_PIN = 3;
static int MOTOR_LB_PIN = 5;
static int MOTOR_RF_PIN = 6;
static int MOTOR_RB_PIN = 9;

Servo servoCX;
Servo servoCY;
Servo servoSX;

int posCY = 90;
int posCX = 90;
int posSX = 90;

void setup() {
  // put your setup code here, to run once:
  servoCX.attach(SERVO_CX_PIN);
  servoCY.attach(SERVO_CY_PIN);
  servoSX.attach(SERVO_SX_PIN);
  Serial.begin(9600);
  
  //set camera servos to default position
  servoCX.write(posCX);
  servoCY.write(posCY);
  
  //set shovel servos to default position
  servoSX.write(posSX);
  
  //set shovel servo pins to output pin mode
  pinMode(SERVO_SX_PIN, OUTPUT);
  
  //set motor pins to output pin mode
  pinMode(MOTOR_LF_PIN, OUTPUT);
  pinMode(MOTOR_LB_PIN, OUTPUT);
  pinMode(MOTOR_RF_PIN, OUTPUT);
  pinMode(MOTOR_RB_PIN, OUTPUT);
  
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
      servoCX.write(180 - value.toInt());
    }
    else if (command == "cy") {
      servoCY.write(180 - value.toInt());
    }
    else if (command == "sx") {
      servoSX.write(180 - value.toInt());
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
