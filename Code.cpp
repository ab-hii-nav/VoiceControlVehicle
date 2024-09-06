#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial mySerial(0, 1); // RX, TX
AF_DCMotor motors[4] = {AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3), AF_DCMotor(4)};
const int motorSpeed = 200;

void setup() {
  Serial.begin(9600); // For debugging
  mySerial.begin(9600); // Voice control
  Serial.println("Ready");
}

void loop() {
  if (mySerial.available()) {
    String voiceCommand = mySerial.readStringUntil('\n');
    Serial.println("Received: " + voiceCommand);

    if (voiceCommand == "go ahead") {
      moveMotors(FORWARD);
    } else if (voiceCommand == "go back") {
      moveMotors(BACKWARD);
    } else if (voiceCommand == "left") {
      rotateLeft();
    } else if (voiceCommand == "right") {
      rotateRight();
    } else if (voiceCommand == "stop") {
      stopMotors();
    }
  }
}

void moveMotors(uint8_t direction) {
  for (int i = 0; i < 4; i++) {
    motors[i].setSpeed(motorSpeed);
    motors[i].run(direction);
  }
}

void rotateLeft() {
  motors[0].setSpeed(motorSpeed);
  motors[1].setSpeed(0);
  motors[2].setSpeed(motorSpeed);
  motors[3].setSpeed(0);
  for (int i = 0; i < 4; i += 2) {
    motors[i].run(BACKWARD);
  }
  for (int i = 1; i < 4; i += 2) {
    motors[i].run(FORWARD);
  }
}

void rotateRight() {
  motors[0].setSpeed(0);
  motors[1].setSpeed(motorSpeed);
  motors[2].setSpeed(0);
  motors[3].setSpeed(motorSpeed);
  for (int i = 0; i < 4; i += 2) {
    motors[i].run(FORWARD);
  }
  for (int i = 1; i < 4; i += 2) {
    motors[i].run(BACKWARD);
  }
}

void stopMotors() {
  for (int i = 0; i < 4; i++) {
    motors[i].setSpeed(0);
    motors[i].run(RELEASE);
  }
}
