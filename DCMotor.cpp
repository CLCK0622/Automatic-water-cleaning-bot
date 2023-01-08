#include <Arduino.h>
#include "DCMotor.h"

void DCMotor::init(int pin) {
  relayPin = pin;
  pinMode(relayPin, OUTPUT);
}

void DCMotor::on() {
  digitalWrite(relayPin, HIGH);
}

void DCMotor::off() {
  digitalWrite(relayPin, LOW);
}