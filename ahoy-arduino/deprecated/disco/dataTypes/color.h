#pragma once

// #include "discoMath.h"
// #include "Arduino.h"
// #include "math"
class Color;
// static_cast<uint64_t>(double_val)

class Color
{
public:
    byte r;
    byte g;
    byte b;
    Color()
    {
        r = 0;
        g = 0;
        b = 0;
    }
    Color(byte val)
    {
        r = val;
        g = val;
        b = val;
    }

    Color(byte _r, byte _g, byte _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }

    // void Print()
    // {
    //     Serial.print("\tRed:\t");
    //     Serial.print(r);
    //     Serial.print("\tGreen:\t");
    //     Serial.print(g);
    //     Serial.print("\tBlue:\t");
    //     Serial.print(b);
    // }

    // String ToJson()
    // {
    //     return "{\"r\":" + String(r) + ",\"g\":" + String(g) + ",\"b\":" + String(b) + "}";
    // }

    static Color Lerp(Color a, Color b, double t)
    {
        return Color(
            Math::Lerp(a.r, b.r, t),
            Math::Lerp(a.g, b.g, t),
            Math::Lerp(a.b, b.b, t));
    }

    static Color FromHSV(double hue, double sat, double val, double max = 1)
    {
        const double incr1 = max / 6;
        const double incr2 = incr1 * 2;
        const double incr3 = incr1 * 3;
        const double incr4 = incr1 * 4;
        const double incr5 = incr1 * 5;
        const double incr6 = incr1 * 6;

        const double chroma = val * sat;
        const int numerator = (hue / incr1) * 1000;
        const double tempVal = ((double)(numerator % 2000) / 1000) - 1;
        // Serial.print("temp num: ");
        // Serial.print(numerator);
        // Serial.print("\ttemp fract: ");
        // Serial.print(tempVal);
        const double x = chroma * (1 - abs(tempVal));
        const double m = val - chroma;

        double colR = 0;
        double colG = 0;
        double colB = 0;

        // if (hue >= 0 && hue < incr1)
        if (hue < incr1)
        {
            colR = chroma;
            colG = x;
        }
        else if (hue >= incr1 && hue < incr2)
        {
            colR = x;
            colG = chroma;
        }
        else if (hue >= incr2 && hue < incr3)
        {
            colG = chroma;
            colB = x;
        }
        else if (hue >= incr3 && hue < incr4)
        {
            colG = x;
            colB = chroma;
        }
        else if (hue >= incr4 && hue < incr5)
        {
            colR = x;
            colB = chroma;
        }
        // else if (hue >= incr5 && hue < incr6)
        else if (hue >= incr5)
        {
            colR = chroma;
            colB = x;
        }
        colR = (colR + m) * 255;
        colG = (colG + m) * 255;
        colB = (colB + m) * 255;
        return Color(colR, colG, colB);
        // background(col.r, col.g, col.b)
    }
};