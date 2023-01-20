#include <Arduino.h>
#include "ST_HW_HC_SR04.h"
#include "HC_SR04.h"

ST_HW_HC_SR04 HC_SR04::mydis() {
  return ST_HW_HC_SR04(this -> trigPin, this -> echoPin);
}

void HC_SR04::init(int trigpin, int echopin) {
  trigPin = trigpin, echopin = echoPin;
  mydis().setTimeout(23200);
}

double HC_SR04::read_dis() {
  dist = mydis().getHitTime();
  dist /= 29;
  if (dist > 400 || dist < 2) return -1;
  return dist;
}