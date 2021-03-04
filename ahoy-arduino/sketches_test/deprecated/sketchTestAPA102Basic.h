#include <FastLED.h>

const int NUM_LEDS = 100;
CRGB ledsRGB[NUM_LEDS];

#define DATA_PIN 13
#define CLOCK_PIN 14

void setup()
{
	Serial.begin(115200);
	// FastLED.addLeds<APA102, 11, 13, RGB, DATA_RATE_MHZ(24)>(ledsRGB, NUM_LEDS);
	// FastLED.addLeds<APA102, 4, 5, BGR, DATA_RATE_MHZ(24)>(ledsRGB, NUM_LEDS);
	// FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(ledsRGB, NUM_LEDS);
	FastLED.addLeds<APA102>(ledsRGB, NUM_LEDS);
	// FastLED.addLeds<APA102, 11, 13>(ledsRGB, NUM_LEDS);
}

byte brightness = 32;

int count = 0;

void loop()
{
	count++;
	for (int i = 0; i < NUM_LEDS; i++)
	{
		ledsRGB[i][0] = 0;
		ledsRGB[i][1] = 0;
		ledsRGB[i][2] = 0;
		if (count % 3 == 0)
			ledsRGB[i][0] = brightness;
		else if (count % 3 == 1)
			ledsRGB[i][1] = brightness;
		else if (count % 3 == 2)
			ledsRGB[i][2] = brightness;

		// ledsRGB[i][2] = fmod((millis() * 0.1), 255);
		// ledsRGB[i].setRGB(0, 0, ); //BRG
	}
	delay(10);
	FastLED.show();
}