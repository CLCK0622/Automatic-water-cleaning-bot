
#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#include <Arduino.h>
#include "ST_HW_HC_SR04.h"

class HC_SR04 {
  public: 
    double read_dis();
    void init(int trigpin, int echopin);
  private:
    double dist;
    int trigPin;
    int echoPin;
    ST_HW_HC_SR04 mydis(); 
};

#endif
