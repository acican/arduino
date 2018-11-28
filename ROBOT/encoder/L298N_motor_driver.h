/*
  Motors298.h - Library for Motors code.
  Released into the public domain.
*/
#ifndef Motors298_h
#define Motors298_h

#include "Arduino.h"
#include "motor_driver.h"
//#include <L298N.h>

#define ENA 8
#define ENB 9
#define N1 28
#define N2 29
#define N3 30
#define N4 31

#define DIST_AXIS 25 		// latime spirala == distanta axe roti
//#define TIME_TURN 6690		// speed 100
#define TIME_TURN 4000		// speed 255

namespace Cican
{
class Motors : public MotorDriver
{
  public:
    Motors(int speed)
          : MotorDriver(), MotorLeft(ENB, N3, N4), MotorRight(ENA, N1, N2), _speedRight(speed), _speedLeft(speed)
	{
		_pinEnableLeft = ENB;
		_pinIN1Left = N3; 
		_pinIN2Left = N4;
		_pinEnableRight = ENA;
		_pinIN1Right = N1;
		_pinIN2Rigt = N2;
		
		currentSpeed = speed;
			  
		_canMove = true;
		_lastMs = 0;
    }
	
	void setSpeedRight(int speed) {
		_speedRight = speed;
		MotorRight.setSpeed(speed);
	}
	
	void setSpeedLeft(int speed) {
		_speedLeft = speed;
		MotorLeft.setSpeed(speed);
	}
        
	int getSpeed() const {
		return currentSpeed;
	}
	
    void MoveStop() {
		MotorRight.stop();
		MotorLeft.stop();
		
		_isMoving = false;
		_canMove = false;
	}
	
	void TurnRightForward(int speed)	{
		this->setSpeedRight(speed);
		MotorRight.forward();

		_isMoving = true;
	}

	void TurnRightBackward(int speed)	{
		this->setSpeedRight(speed);
		MotorRight.backward();

		_isMoving = true;
	}

	void MoveForward(int speed)	{
		this->setSpeedRight(speed);
		this->setSpeedLeft(speed);
		MotorRight.forward();
		MotorLeft.backward();
		
		_isMoving = true;
	}

	void MoveBackward(int speed) {
		this->setSpeedRight(speed);
		this->setSpeedLeft(speed);
		MotorRight.backward();
		MotorLeft.forward();
		
		_isMoving = true;
	}

	void TurnLeft() {
		this->setSpeedRight(255);
		this->setSpeedLeft(255);
		MotorRight.backward();
		MotorLeft.backward();
		int tmp = (int)(TIME_TURN/2); 
		delay(tmp);
		this->MoveStop();
	}

	void TurnRight() {
		this->setSpeedRight(255);
		this->setSpeedLeft(255);
		MotorRight.forward();
		MotorLeft.forward();
		int tmp = (int)(TIME_TURN/2); 
		delay(tmp);
		this->MoveStop();
	}
	
	void MoveForwardLeft(int delay, int speed) {
		if ((_lastMs == 0) && _canMove) {
			_lastMs = millis();
			this->setSpeedRight(speed);
			this->setSpeedLeft(255);
			MotorRight.forward();
			MotorLeft.backward();
		}		

		if (((millis() - _lastMs) > delay) && _canMove) {
			this->MoveStop();
			_lastMs = 0;
			_canMove = false;
		}
	}
	
	void MoveForwardRight(int delay, int speed) {
		if ((_lastMs == 0) && _canMove) {
			_lastMs = millis();
			this->setSpeedRight(255);
			this->setSpeedLeft(speed);
			MotorRight.forward();
			MotorLeft.backward();
		}		

		if (((millis() - _lastMs) > delay) && _canMove) {
			this->MoveStop();
			_lastMs = 0;
			_canMove = false;
		}
	}
	
	void MoveBackwardRight(int delay, int speed) {
		if ((_lastMs == 0) && _canMove) {
			_lastMs = millis();
			this->setSpeedRight(255);
			this->setSpeedLeft(speed);
			MotorRight.backward();
			MotorLeft.forward();
		}		

		if (((millis() - _lastMs) > delay) && _canMove) {
			this->MoveStop();
			_lastMs = 0;
			_canMove = false;
		}
	}
	
	void MoveBackwardLeft(int delay, int speed) {
		if ((_lastMs == 0) && _canMove) {
			_lastMs = millis();
			this->setSpeedRight(speed);
			this->setSpeedLeft(255);
			MotorRight.backward();
			MotorLeft.forward();
		}		

		if (((millis() - _lastMs) > delay) && _canMove) {
			this->MoveStop();
			_lastMs = 0;
			_canMove = false;
		}
	}
	
	void MoveSpiral(unsigned long delay, int speed)	{
		if ((_lastMs == 0) && _canMove)	{
			_lastMs = millis();
			_timeUp = millis();
			nextUp = TIME_TURN;             // timp increment time si speed MotorLeft
			n = 1.0;
      
			_speedRight = speed;
			_speedLeft = 0;  
			
			MotorRight.setSpeed(_speedRight);
			MotorRight.forward();

			MotorLeft.setSpeed(_speedLeft);
			MotorLeft.backward();
			_speedLeft = 33;
			
        }
		
		if (((millis() - _timeUp) >= nextUp) && _canMove) {
			n = n + 0.3;
//			_speedLeft = (int)(_speedRight * (n - 1) / n);
			nextUp = (int)(nextUp * (n + 0.3) / n);
 
			MotorLeft.setSpeed(_speedLeft);
			MotorLeft.backward();
			_timeUp = millis();
			_speedLeft = _speedLeft+ 10;  // increment fix
			

			Serial.print("Timp : "); Serial.print(millis()); Serial.print(" Salt : "); Serial.print(nextUp);
			Serial.print(" n : "); Serial.print(n,2); Serial.print(" speed : ");  Serial.println(_speedLeft);
		} 
		
//		if (((millis() - _lastMs) > delay) {
		if (n > 3) {	
			this->MoveStop();
			_lastMs = 0;
			_canMove = false;

		}

    }
	
	void forwardFor(unsigned long delay, CallBackFunction callback) {
		if ((_lastMs == 0) && _canMove) {
			_lastMs = millis();
			this->MoveForward(100);
		}		

		if (((millis() - _lastMs) > delay) && _canMove) {
			this->MoveStop();
			_lastMs = 0;
			_canMove = false;

			callback();

		}
	}

	void forwardFor(unsigned long delay) {
		this->forwardFor(delay, fakeCallback);
	}
	
	
	void reset() {
		_canMove = true;
		_lastMs = 0;
	}

	boolean isMoving() {
		return _isMoving;
	}
	
	boolean canMoving() {
		return _canMove;
	}
	
  private:
  
    L298N MotorLeft, MotorRight;
	
	byte _pinEnableLeft, _pinIN1Left, _pinIN2Left;
	byte _pinEnableRight, _pinIN1Right, _pinIN2Rigt;
    
    int _speedRight, _speedLeft;
    int currentSpeed;
	
	unsigned long _lastMs;
	unsigned long _currTime, nextUp, _timeUp;
    float n;
    	
    boolean _canMove;
    boolean _isMoving;
	
	static void fakeCallback() {

    }
};
};

#endif
