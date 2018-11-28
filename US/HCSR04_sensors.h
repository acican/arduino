/*
  Motors298.h - Library for Motors code.
  Released into the public domain.
*/
#ifndef SensorsHCSR04_h
#define SensorsHCSR04_h

#include "Arduino.h"
#include "HCSR04.h"

#define EchoRight 22
#define TrigRight 23
#define EchoFront 24
#define TrigFront 25
#define EchoLeft 26
#define TrigLeft 27


namespace Cican
{
class Sensors
{
  public:
    Sensors()
          : SensorLeft(EchoLeft, TrigLeft), SensorRight(EchoRight, TrigRight), SensorFront(EchoFront, TrigFront)
	  {
		  _trigPinLeft = TrigLeft;
		  _trigPinRight = TrigRight; 
		  _trigPinFront = TrigFront;
		  _echoPinLeft = EchoLeft;
		  _echoPinRight = EchoRight;
		  _echoPinFront = EchoFront;
    }
	
	  long distanceLeft() {
      long distance;
      distance = SensorLeft.distance();
      return distance;
	  }
	
	  long distanceRight() {
      long distance;
      distance = SensorRight.distance();
      return distance;
	  }
	
	  long distanceFront() {
      long distance;
      distance = SensorFront.distance();
      return distance;
	  }

	
  private:
  
    HCSR04 SensorLeft, SensorRight, SensorFront;
	
	  byte _trigPinLeft, _trigPinRight, _trigPinFront;
	  byte _echoPinLeft, _echoPinRight, _echoPinFront;

  };
};

#endif
