#include <Servo.h>

Servo solarServo;
const int ldrLeft = A0;
const int ldrRight = A1;
const int servoPin = 9;
int servoAngle = 90;
int stepSize = 2;
int threshold = 40;
unsigned long lastImprovement = 0;
unsigned long failSafeDelay = 60000;
float Q_left = 0;
float Q_right = 0;
float alpha = 0.5;
float gamma = 0.8;

void setup() {
  Serial.begin(9600);
  solarServo.attach(servoPin);
  solarServo.write(servoAngle);
  lastImprovement = millis();
}

void loop() {
  int leftLight = analogRead(ldrLeft);
  int rightLight = analogRead(ldrRight);
  int difference = leftLight - rightLight;
  int reward = abs(difference);

  if (difference > threshold) {
    Q_left = Q_left + alpha * (reward + gamma * Q_left - Q_left);
    servoAngle -= stepSize;
    servoAngle = constrain(servoAngle, 0, 180);
    solarServo.write(servoAngle);
    lastImprovement = millis();
  } else if (difference < -threshold) {
    Q_right = Q_right + alpha * (reward + gamma * Q_right - Q_right);
    servoAngle += stepSize;
    servoAngle = constrain(servoAngle, 0, 180);
    solarServo.write(servoAngle);
    lastImprovement = millis();
  }

  if (millis() - lastImprovement > failSafeDelay) {
    servoAngle += 1;
    if (servoAngle > 180) servoAngle = 0;
    solarServo.write(servoAngle);
    lastImprovement = millis();
  }

  Serial.print("Left LDR: ");
  Serial.print(leftLight);
  Serial.print(" Right LDR: ");
  Serial.print(rightLight);
  Serial.print(" Servo Angle: ");
  Serial.println(servoAngle);
  delay(200);
}
