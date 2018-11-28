/*
  Library Body - HCSR04 ultrasonic sensor.
  Adrian Cican
  acican@gmail.com
*/

#include "Arduino.h"
#include "HCSR04.h"

HCSR04::HCSR04(uint8_t echoPin, uint8_t trigPin)
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
  delayMicroseconds(5);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(_trigPin, LOW);
  duration = pulseIn(_echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  return distance;
}
