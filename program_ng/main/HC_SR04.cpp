#include <Arduino.h>
#include "HC_SR04.h"

void HC_SR04::init(int trigpin, int echopin) {
  trigPin = trigpin, echoPin = echopin;
  pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	Serial.begin(9600);
}

double HC_SR04::get_dis() {
  digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
	return distance;
}