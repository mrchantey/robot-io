#pragma once
// const uint32_t max16 = pow(2, sizeof(uint16_t) * 8) - 1;
// const uint32_t max8 = pow(2, sizeof(uint8_t) * 8) - 1;
// const int32_t absMax8 = pow(2, sizeof(uint8_t) * 8);
// const int32_t min8 = 0 - (absMax8 / 2);
// const int32_t max8 = absMax8 - (absMax8 - absMax8 / 2) - 1;

// const int32_t absMax16 = pow(2, sizeof(uint16_t) * 8);
// const int32_t min16 = 0 - (absMax16 / 2);
// const int32_t max16 = absMax16 - (absMax16 - absMax16 / 2) - 1;

class Math
{
public:
    template <typename T1>
    static T1 Lerp(T1 a, T1 b, float t)
    {
        return a + t * (b - a);
    };

    static int WrapInt(int val, int max)
    {
        return ((val % max) + max) % max;
    }
    static float WrapFloat(float val, float max)
    {
        return fmod(fmod(val, max) + max, max);
    }
    static double WrapDouble(double val, double max)
    {
        return fmod(fmod(val, max) + max, max);
    }

    // template <typename T1>
    // static float Map(float val, float min1, float max1, float min2, float max2)
    // {
    //     return min2 + (max2 - min2) * ((val - min1) / (max1 - min1));
    // }

    static double Map(double val, double min1, double max1, double min2, double max2)
    {
        return min2 + (max2 - min2) * ((val - min1) / (max1 - min1));
    }

    // static int8_t MapInt16To8(int16_t val)
    // {
    //     return Map(val, min16, max16, min8, max8);
    // }

    // static uint8_t MapInt16To8(uint16_t val16)
    // {
    //     float valNormal = (float)val16 / max16;
    //     return valNormal * max8;
    // }
};