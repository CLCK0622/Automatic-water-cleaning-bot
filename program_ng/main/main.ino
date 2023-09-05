#include <Arduino.h>
#include "HC_SR04.h"

HC_SR04 dis1, dis2;

void setup() {
  // put your setup code here, to run once:
  dis1.init(9, 10);
  dis2.init(12, 13);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Dis1: ");
  Serial.println(dis1.get_dis());
  Serial.print("Dis2: ");
  Serial.println(dis2.get_dis());
  delay(500);
}
