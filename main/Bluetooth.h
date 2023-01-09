
#ifndef _Bluetooth_H_
#define _Bluetooth_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class Bluetooth {
  public:
    void init();
    Bluetooth(int, int);
    void send(char s);
    bool test();
    char receive();
  private:
    SoftwareSerial Tmp();
    int rxPin;
    int txPin;
};

#endif
