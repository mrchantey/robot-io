#pragma once;
#include <FastLED.h>

/* 
 * Hack to enable SK6812 RGBW strips to work with FastLED.
 *
 * Original code by Jim Bumgardner (http://krazydad.com).
 * Modified by David Madison (http://partsnotincluded.com).
 * 
*/

struct CRGBW
{
    union {
        struct
        {
            union {
                uint8_t g;
                uint8_t green;
            };
            union {
                uint8_t r;
                uint8_t red;
            };
            union {
                uint8_t b;
                uint8_t blue;
            };
            union {
                uint8_t w;
                uint8_t white;
            };
        };
        uint8_t raw[4];
    };

    CRGBW() {}

    CRGBW(uint8_t rd, uint8_t grn, uint8_t blu, uint8_t wht)
    {
        r = rd;
        g = grn;
        b = blu;
        w = wht;
    }

    inline void operator=(const CRGB c) __attribute__((always_inline))
    {
        this->r = c.r;
        this->g = c.g;
        this->b = c.b;
        this->white = 0;
    }
};

inline uint16_t getRGBWsize(uint16_t nleds)
{
    uint16_t nbytes = nleds * 4;
    if (nbytes % 3 > 0)
        return nbytes / 3 + 1;
    else
        return nbytes / 3;
}

// CRGBW leds[NUM_LEDS];
// CRGB *ledsRGB = (CRGB *) &leds[0];

//     void setup() {
// //      FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
//       FastLED.addLeds<WS2812, LED_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));

//     }
//     int count = 0;
//     void loop() {
//       count = (count + 1) % NUM_LEDS;
//       leds[count] = CRGBW(0, 32, 0,0);
//       FastLED.show();
// //      delayMicroseconds(20);
//       leds[count] = CRGBW(0, 0, 0,0);
//       FastLED.show();
//     }
