#include <Arduino.h>
#include "HC_SR04.h"
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <Servo.h>

HC_SR04 disLeft, disRight;
HUSKYLENS lens;
Servo ang, box;

// here to declare const variables:
const int servoPin = 3;
const int boxPin = 5;
const int motorPin = 7;
const int passerPin = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Wire.begin();
  while (!lens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("Please check!"));
    delay(100);
  }
  
  disLeft.init(9, 10);
  disRight.init(12, 13);

  pinMode(servoPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(passerPin, OUTPUT);
  pinMode(boxPin, OUTPUT);

  ang.attach(servoPin, 500, 2500);
  box.attach(boxPin, 500, 2500);
  ang.write(110);
  box.write(90);

  Serial.println("Init successfully! ");
}

void loop() {
  // initialize the variables here:
  int offset = 5;
  HUSKYLENSResult result;

  // put your main code here, to run repeatedly:
  digitalWrite(passerPin, HIGH);

  if (!tracked) {
    forward();
    while ((disLeft.get_dis() > 5 && disLeft.get_dis() < 150) || (disRight.get_dis() > 5 && disRight.get_dis() < 150)) {
      if (disLeft.get_dis() > 150) {
        left();
      } else if (disRight.get_dis() > 150) {
        right();
      } else {
        stop();
      }
    }
  } else {
    while (getTargetX < -offset) {
      left();
    }
    while (getTargetX > offset) {
      right();
    }
  }

  if (!lens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, check the connection! "));
  } else if (!lens.isLearned()) {
    Serial.println(F("Nothing learned, press learn button on the HUSKYLENS first! "));
  } else if (!lens.available()) {
    Serial.println(F("No target found! "));
  } else {
    if (lens.available()) {
      result = lens.read();
    }
  }
}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(", yCenter=") + result.yCenter);
  } else {
    Serial.println("Object unknown! ");
  }
}

void forward() {
  Serial.println("forward");
  digitalWrite(motorPin, HIGH);
  ang.write(110);
  return ;
}

void stop() {
  Serial.println("stop");
  digitalWrite(motorPin, LOW);
  ang.write(110);
  return ;
}

void left() {
  Serial.println("left");
  ang.write(80);
  return ;
}

void right() {
  Serial.println("right");
  ang.write(110);
  return ;
}

bool tracked() {
  if (lens.available()) {
    return true;
  } else {
    return false;
  }
}

double getTargetX(HUSKYLENSResult result) {
  if (tracked() && result.command == COMMAND_RETURN_BLOCK) {
    return result.xCenter;
  }
  return 0;
}