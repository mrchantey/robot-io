#pragma once

class Vector3Int
{
  public:
    int16_t x;
    int16_t y;
    int16_t z;
    Vector3Int()
    {
        x, y, z = 0;
    }

    Vector3Int(int16_t _x, int16_t _y, int16_t _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void
    Print()
    {
        Serial.print("x:\t");
        Serial.print(x);
        Serial.print("y:\t");
        Serial.print(y);
        Serial.print("z:\t");
        Serial.print(z);
        Serial.print("\t");
    };

    String ToString()
    {
        return String("") + "x:" + x + "\ty:" + y + "\tz:" + z;
    }

    String ToJson()
    {
        return String("") + "{\"x\":" + x + ",\"y\":" + y + ",\"z\":" + z + "}";
    }

    ubyte *ToByteArray()
    {
        ubyte arr[3];
        arr[0] = Data::MapUIntToUbyte(x);
        arr[1] = Data::MapUIntToUbyte(y);
        arr[2] = Data::MapUIntToUbyte(z);
        return arr;
    }

    void operator+=(Vector3Int vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }

    static Vector3Int Map(Vector3Int vec, uint min1, uint max1, uint min2, uint max2)
    {
        return Vector3Int(
            map(vec.x, min1, max1, min2, max2),
            map(vec.y, min1, max1, min2, max2),
            map(vec.z, min1, max1, min2, max2));
    }
};