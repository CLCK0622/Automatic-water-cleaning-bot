
#ifndef _DCMotor_H_
#define _DCMotor_H_

#include <Arduino.h>

class DCMotor {
  public:
    void init(int pin);
    void on();
    void off();
  private:
    int relayPin;
};

#endif