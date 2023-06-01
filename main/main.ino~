#include <Arduino.h>
#include <Servo.h>
#include "HC_SR04.h"

const int servoControl = 3;
const int motorControl = 9;
const int passerControl = 13;
const int boxControl = 10;
const int servoPin = 11;
const int motorPin = 2;
const int passerPin = 8;
const int boxPin = 12;
const int leftTrig = 4, leftEcho = 5; 
const int rightTrig = 6, rightEcho = 7;

HC_SR04 disLeft;
HC_SR04 disRight;
int leftDis;
int rightDis;

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
    servoVal = pulseIn(servoControl, HIGH); //使用外部中断读取控制器
    motorVal = pulseIn(motorControl, HIGH);
    passerVal = pulseIn(passerControl, HIGH);
    boxVal = pulseIn(boxControl, HIGH);
    // if (servoVal > 1480 && servoVal < 2000) { //手控转向逻辑
    //     mys.write(servoCalc(servoVal));
    //     Serial.println("left");
    // } else if (servoVal < 1400 && servoVal > 900) {
    //     mys.write(servoCalc(servoVal));
    //     Serial.println("right");
    // } else {
    //     mys.write(110);
    // }
    leftDis = disLeft.read_dis(); //读取超声波数值
    rightDis = disRight.read_dis();
    Serial.print("left: "); //调试输出
    Serial.print(leftDis);
    Serial.print("\n right: ");
    Serial.println(rightDis);
    if (leftEnough() && rightEnough()) { //超声波避障功能设计
        if (cam.left()) {
            mys.write(80);
        } else if (cam.right()) {
            mys.write(110);
        } else {
            mys.write(110);
        }
    } else if (!leftEnough() && !rightEnough()) {
        if (leftDis < rightDis) {
            mys.write(140);
        } else {
            mys.write(80);
        }
    } else {
        mys.write(110);
    }
    // Serial.println(servoVal);
    if (!(motorVal > 900 && motorVal < 1000)) { //运动手控逻辑设计
    // if (leftDis < 200 && rightDis < 200) {
        digitalWrite(motorPin, LOW);
        Serial.println("stop");
    } else if (!leftEnough() && !rightEnough) {
        digitalWrite(motorPin, LOW);
        // will add motor control and support go back
    } else {
        digitalWrite(motorPin, HIGH);
    }
    // Serial.println(passerVal);
    if (passerVal < 1000 && passerVal > 900 || cam.getRubbish()) { //自动&手控垃圾收入逻辑
        digitalWrite(passerPin, HIGH);
        Serial.println("rubbishIn");
    } else {
        digitalWrite(passerPin, LOW);
    }
    if (boxVal < 1000 && boxVal > 900) { //垃圾倾倒手控逻辑设计
        //will add automatic clean-up support
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

bool leftEnough() {
    if (leftDis > 200 || leftDis < 5) {
        return true;
    }
    return false;
}

bool rightEnough() {
    if (rightDis > 200 || rightDis < 5) {
        return true;
    }
    return false;
}
