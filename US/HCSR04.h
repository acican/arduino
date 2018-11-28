/*
  Sensors.h - Library for Sensors code.
  Released into the public domain.
*/
#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

namespace Cican
{
class HCSR04
{
  public:
    HCSR04(uint8_t trigPin, uint8_t echoPin);
    long distance();
  private:
	  uint8_t _trigPin;
	  uint8_t _echoPin;
};
};

#endif
