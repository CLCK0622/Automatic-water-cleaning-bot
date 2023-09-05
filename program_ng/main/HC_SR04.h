
#ifndef _HC_SR04_
#define _HC_SR04_

#include <Arduino.h>

class HC_SR04 {
  public: 
    void init(int trigpin, int echopin);
    double get_dis();
  private:
    int trigPin, echoPin;
    double duration, distance;
};

#endif
