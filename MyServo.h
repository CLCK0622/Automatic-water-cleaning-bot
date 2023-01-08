
#ifndef _MyServo_H_
#define _MyServo_H_

#include <Arduino.h>
#include "Servo.h"

class MyServo {
  public:
    void reset();
    void init(int pin);
    void set_ang(int ang);
  private:
    Servo mys;
};

#endif
