
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Bluetooth.h"

SoftwareSerial Bluetooth::Tmp() {
  return SoftwareSerial(this -> rxPin, this -> txPin);
}

Bluetooth::Bluetooth(int RxPin, int TxPin) {
  rxPin = RxPin, txPin = TxPin;
}

void Bluetooth::init() {
  Tmp().begin(9600);
  Tmp().println("Bluetooth remote control finished initializing! ");
}

bool Bluetooth::test() {
  return Tmp().available();
}

char Bluetooth::receive() {
  if (Tmp().available()) {
    char res = Tmp().read();
    return res;
  } else {
    return '0';
  }
}

void Bluetooth::send(char s) {
  Tmp().print(s);
}