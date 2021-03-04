#pragma once

class MotorHBridge
{

protected:
	int pinFwd;
	int pinRev;

public:
	MotorHBridge(int _pinFwd, int _pinRev)
	{
		pinFwd = _pinFwd;
		pinRev = _pinRev;
		pinMode(pinFwd, OUTPUT);
		pinMode(pinRev, OUTPUT);
	}

	void SetSpeed(float speed)
	{
		if (speed > 0)
		{
			digitalWrite(pinRev, false);
			analogWrite(pinFwd, (int)(speed * 255));
		}
		else if (speed < 0)
		{
			digitalWrite(pinFwd, false);
			analogWrite(pinRev, speed * -255);
		}
		else
		{
			digitalWrite(pinFwd, false);
			digitalWrite(pinRev, false);
		}
	}
};