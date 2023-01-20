#include <Arduino.h>
#include <Servo.h>
#include "HC_SR04.h"

const int servoControl = 3;
const int motorControl = 9;
const int passerControl = 6;
const int boxControl = 10;
const int servoPin = 7;
const int motorPin = 2;
const int passerPin = 8;
const int boxPin = 12;
const int leftTrig, leftEcho, rightTrig, rightEcho;

HC_SR04 disLeft;
HC_SR04 disRight;

Servo mys;
Servo box;

int servoVal;
int motorVal;
int passerVal;
int boxVal;

void setup() {
    pinMode(servoControl, INPUT);
    pinMode(motorControl, INPUT);
    pinMode(passerControl, INPUT);
    pinMode(boxControl, INPUT);
    Serial.begin(115200);
    pinMode(servoPin, OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(passerPin, OUTPUT);
    pinMode(boxPin, OUTPUT);
    mys.attach(servoPin, 500, 2500);
    box.attach(boxPin, 500, 2500);
    mys.write(110);
    box.write(90);
    disLeft.init(leftTrig, leftEcho);
    disRight.init(rightTrig, rightEcho);
    while (!Serial);
    Serial.println("Init successfully! ");
}

void loop() {
    servoVal = pulseIn(servoControl, HIGH);
    motorVal = pulseIn(motorControl, HIGH);
    passerVal = pulseIn(passerControl, HIGH);
    boxVal = pulseIn(boxControl, HIGH);
    if (servoVal > 1480 && servoVal < 2000) {
        mys.write(servoCalc(servoVal));
        Serial.println("left");
    } else if (servoVal < 1400 && servoVal > 900) {
        mys.write(servoCalc(servoVal));
        Serial.println("right");
    } else {
        mys.write(110);
    }
    // Serial.println(servoVal);
    int leftDis = disLeft.read_dis();
    int rightDis = disRight.read_dis();
    // if (motorVal < 1350 && motorVal > 900) {
    if (leftDis < 150 && rightDis < 150) {
        digitalWrite(motorPin, HIGH);
        Serial.println("forward");
    } else if (leftDis < 150) {
        mys.write(95);
    } else if (rightDis < 150) {
        mys.write(125);
    } else {
        digitalWrite(motorPin, LOW);
        // will add motor control and support go back
    }
    // Serial.println(passerVal);
    if (passerVal < 1000 && passerVal > 900) {
        digitalWrite(passerPin, HIGH);
        Serial.println("rubbishIn");
    } else {
        digitalWrite(passerPin, LOW);
    }
    if (boxVal < 1000 && boxVal > 900) {
        box.write(75);
        Serial.println("Box up");
    } else if (boxVal > 1900 && boxVal < 2000) {
        box.write(105);
        Serial.println("Box down");
    } else {
        box.write(90);
    }
    // Serial.println(boxVal);
}

int servoCalc(int val) {
    return (110 + (double(val) - 1450) / 250 * 40);
    /*
    servoVal:
      range: 1200-1700
      default: 1450
      single_range: 250
      (Val - 1450) / 250 * 40
    */
}