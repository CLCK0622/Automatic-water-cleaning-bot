#include <Arduino.h>
#include "MyServo.h"

void MyServo::reset() {
  mys.write(120);
}

void MyServo::init(int pin) {
  pinMode(pin, OUTPUT);
  mys.attach(pin, 500, 2500);
  mys.write(60);
  delay(1000);
  mys.write(175);
  delay(1000);
  mys.write(120);
}

void MyServo::set_ang(int ang) {
  mys.write(ang);
}
