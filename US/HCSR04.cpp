/*
  Sensors.cpp - Library for Sensors code.
  Released into the public domain.
*/

#include "Arduino.h"
#include "HCSR04.h"

namespace Cican
{
HCSR04::HCSR04(uint8_t trigPin, uint8_t echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  _trigPin = trigPin;
  _echoPin = echoPin;
}

long HCSR04::distance()
{
  long duration, distance;
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  duration = pulseIn(_echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  return distance;	  
}
};
