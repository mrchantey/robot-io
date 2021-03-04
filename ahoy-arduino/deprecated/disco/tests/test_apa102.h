#define FASTLED_FORCE_SOFTWARE_SPI
#include <FastLED.h>
#define DATA_PIN 11
#define CLK_PIN 13
#define LED_TYPE APA102
#define COLOR_ORDER BGR
//#define NUM_LEDS  360
#define NUM_LEDS 36
CRGB leds[NUM_LEDS];

ubyte val1 = 255;
ubyte val2 = 0;
ubyte val3 = 255;
//int del = 100;
uint val4 = 50;

ubyte getValue(int pin)
{
    int a = analogRead(pin);
    float b = pow((float)a / 1024, 0.2);
    return b * 255;
}

void initPots()
{
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

void show(CRGB col)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = col;
    }
    FastLED.show();
    delay(val4);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("hello world");
    FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

    while (true)
    {
        val1 = getValue(A0);
        val2 = getValue(A1);
        val3 = getValue(A2);
        val4 = analogRead(A3);
        char buf[60];
        sprintf(buf, "val1: %d\tval2: %d\tval3: %d\tval4: %d", val1, val2, val3, val4);
        Serial.println(buf);
        CRGB col1 = CRGB(val1, val2, val3);
        CRGB col2 = CRGB(val3, val1, val2);
        CRGB col3 = CRGB(val2, val3, val1);
        show(col1);
        show(col2);
        show(col3);
    }
}