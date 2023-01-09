#include <Arduino.h>
#include "HC_SR04.h"
#include "DCMotor.h"
#include "MyServo.h"
#include "Husky.h"
#include "Bluetooth.h"

HC_SR04 disleft;
HC_SR04 disright;
int disPin[4] = {5, 6, 7, 8}; //超声波接口

DCMotor mot;
int motPin = 9;

// Bluetooth bt(2, 3);

void prepare();
void warn();
int ledsdPin = 0;

int servoPin = 2;
MyServo servo;
int left_ang = 60, right_ang = 175, def_ang = 120;

Husky cam;
int camPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // disleft.init(disPin[0], disPin[1]);
  // disright.init(disPin[2], disPin[3]);
  mot.init(motPin);
  // servo.init(servoPin);
  // cam.init(camPin);
  // bt.init();
  pinMode(13, INPUT);
  Serial.println("Init successfully! ");
  // prepare();
}

void loop() {
  // put your main code here, to run repeatedly:
  // servo.set_ang(def_ang);
  // mot.off();
  // delay(1000);
  // mot.on();
  // delay(1000);
  // while (disleft.read_dis() < 150 || disright.read_dis() < 150) {
  //   warn();
  //   if (disleft.read_dis() < 150) servo.set_ang(right_ang);
  //   else if (disright.read_dis() < 150) servo.set_ang(left_ang);
  // }
  // if (cam.fd_tra()) {
  //   if (cam.tra_posx() < 150) servo.set_ang(left_ang);
  //   else if (cam.tra_posx() > 170) servo.set_ang(right_ang);
  //   else servo.set_ang(def_ang);
  // } else {
  //   servo.set_ang(def_ang);
  // }
  if (digitalRead(13) != HIGH) {
    mot.on();
    delay(1000);
  } else {
    mot.off();
    delay(1000);
  }
}

void prepare() {
  pinMode(ledsdPin, OUTPUT);
  digitalWrite(ledsdPin, HIGH);
  delay(3000);
  digitalWrite(ledsdPin, LOW);
}

void warn() {
  pinMode(ledsdPin, OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledsdPin, HIGH);
    delay(200);
    digitalWrite(ledsdPin, LOW);
  }
}

/*
开机：
向前1s
舵机左1s中1s右1s
LED灯闪烁3次 蜂鸣器鸣叫3次
运行：
找到垃圾（红灯 蜂鸣器1s1次）：
垃圾在视野左侧：向左
右侧：向右
向前走；
未找到垃圾（橙灯 蜂鸣器不动）：
持续向前
若左/右侧小于100cm则向另一侧转向
若前侧小于100cm则向左右小的转向

*/