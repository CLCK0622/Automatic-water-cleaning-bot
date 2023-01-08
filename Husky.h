
#ifndef _Husky_H_
#define _Husky_H_

#include <Arduino.h>
#include "HUSKYLENS.h"

class Husky {
  public:
    bool fd_tra();
    int tra_posx();
    void init(int pin);
  private:
    int camPin;
    HUSKYLENS lens;
};

#endif