#include <Arduino.h>
#include "Husky.h"
#include "HUSKYLENS.h"

void Husky::init(int pin) {
  camPin = pin;
  pinMode(A0, INPUT_PULLUP);
  Wire.begin();
  while (!lens.begin(Wire)) {
    Serial.println(F("Begin Failed! "));
    delay(200);
  }
}

bool Husky::fd_tra() {
  if (!lens.request()) Serial.println(F("Fail to request data form Huskylens, check the connection! "));
  else if (!lens.isLearned()) Serial.println(F("Nothing has been learned yet! "));
  else if (!lens.available()) Serial.println(F("No block detected! "));
  else {
    return true;
  }
  return false;
}

int Husky::tra_posx() {
  if (lens.available()) {
    HUSKYLENSResult res = lens.read();
    if (res.command == COMMAND_RETURN_BLOCK) {
      return res.xCenter;
    }
  }
  return -1;
}