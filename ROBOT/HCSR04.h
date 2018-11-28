/*
  Library Header - HCSR04 ultrasonic sensor.
  Adrian Cican
  acican@gmail.com
*/

#ifndef HCSR04_h
#define HCSR04_h

#include "Arduino.h"

class HCSR04
{
  public:
    HCSR04(uint8_t trigPin, uint8_t echoPin);
    long distance();
  private:
    uint8_t _trigPin;
    uint8_t _echoPin;
};

#endif
