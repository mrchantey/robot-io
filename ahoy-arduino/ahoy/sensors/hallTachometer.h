
void ___tachOnTrigger();

class HallTachometer
{
private:
public:
	long lastTick = 0;
	long deltaTick = 1000;
	bool wasTriggered = false;
	float fraction;
	HallTachometer(byte pin)
	{
		pinMode(pin, INPUT_PULLUP);
		attachInterrupt(digitalPinToInterrupt(pin), ___tachOnTrigger, FALLING);
	}

	void Update()
	{
		long currentTime = millis();
		long thisDelta = currentTime - lastTick;

		fraction = (float)thisDelta / deltaTick;
		// Serial.println(fraction);
	}
};
HallTachometer *___tach;

void ___tachOnTrigger()
{
	long prevTick = ___tach->lastTick;
	___tach->lastTick = millis();
	___tach->deltaTick = ___tach->lastTick - prevTick;
}

HallTachometer *CreateHallTachometer(byte pin)
{
	___tach = new HallTachometer(pin);
	return ___tach;
}
