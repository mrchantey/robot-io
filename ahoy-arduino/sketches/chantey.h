#include "../ahoy/chanteyDevice.h"

ChanteyDevice *chanteyDevice;

void setup()
{
	chanteyDevice = new ChanteyDevice();
}

void loop()
{
	chanteyDevice->Update();
}