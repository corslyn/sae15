#include "CarMotors.h"

void CarMotors::init(uint8_t p_speed) {
  currentSpeed = p_speed;
  isMoving = false;
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
}

void CarMotors::goForward() {
  isMoving = true;
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, currentSpeed);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, currentSpeed);
}

void CarMotors::goBackward() {
  isMoving = true;
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, currentSpeed);
  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, currentSpeed);
}

void CarMotors::turnLeft() {
  isMoving = true;
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, currentSpeed);
  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, currentSpeed);
}

void CarMotors::turnRight() {
  isMoving = true;
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, currentSpeed);
  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, currentSpeed);
}

void CarMotors::drive(float leftCoef,float rightCoef) {
  isMoving = true;
  if (leftCoef<-1.0f) leftCoef=-1.0f;
  if (leftCoef>1.0f) leftCoef=1.0f;
  if (rightCoef<-1.0f) rightCoef=-1.0f;
  if (rightCoef>1.0f) rightCoef=1.0f;
  digitalWrite(PIN_Motor_STBY, HIGH);
  digitalWrite(PIN_Motor_AIN_1, leftCoef>0.0f?HIGH:LOW);
  analogWrite(PIN_Motor_PWMA, leftCoef*currentSpeed);
  digitalWrite(PIN_Motor_BIN_1, rightCoef>0.0f?HIGH:LOW);
  analogWrite(PIN_Motor_PWMB, rightCoef*currentSpeed);
}

void CarMotors::stop() {
  isMoving = false;
  digitalWrite(PIN_Motor_STBY, LOW);
  analogWrite(PIN_Motor_PWMA, 0);
  analogWrite(PIN_Motor_PWMB, 0);
}

