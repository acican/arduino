/*
  MotorsDrive.h - Parent library for Motors code.
  Released into the public domain.
*/

namespace Cican
{
    class MotorDriver
    {
    public:
        virtual void setSpeedRight(int speed) = 0;
        virtual void setSpeedLeft(int speed) = 0;
        virtual int getSpeed() const = 0;

	private:
//		int _speedRight, _speedLeft;
//		int currentSpeed;

    };
};
