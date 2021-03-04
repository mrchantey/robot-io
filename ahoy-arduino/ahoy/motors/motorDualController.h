#pragma once

#include "./motorHBridge.h"
#include "../utility/utility.h"
#include "../led/definitions.h"

class MotorDualController
{

public:
	MotorHBridge *leftMotor;
	MotorHBridge *rightMotor;
	MotorDualController(int _pinLFwd, int _pinLRev, int _pinRFwd, int _pinRRev)
	{
		leftMotor = new MotorHBridge(_pinLFwd, _pinLRev);
		rightMotor = new MotorHBridge(_pinRFwd, _pinRRev);
	}

	void SetSpeed(float speed)
	{
		leftMotor->SetSpeed(speed);
		rightMotor->SetSpeed(speed);
	}

	void SetSpeeds(float speedL, float speedR)
	{
		leftMotor->SetSpeed(speedL);
		rightMotor->SetSpeed(speedR);
	}

	void ParseValuesBuffer(char **valuesBuffer, int index = 0)
	{
		int key = atoi(valuesBuffer[index++]);
		MessageKey msgKey = static_cast<MessageKey>(key);
		if (key == MKEY_MOTOR_SPEED)
		{
			float speed = atof(valuesBuffer[index++]);
			SetSpeed(speed);
		}
		if (valuesBuffer[index] != NULL)
			ParseValuesBuffer(valuesBuffer, index);
	}
};
