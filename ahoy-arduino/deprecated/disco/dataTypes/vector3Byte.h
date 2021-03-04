

class Vector3Byte
{

  public:
    ubyte x;
    ubyte y;
    ubyte z;
    Vector3Byte(Vector3Int val)
    {
        x = Data::MapUIntToUbyte(val.x);
        y = Data::MapUIntToUbyte(val.y);
        z = Data::MapUIntToUbyte(val.z);
    }
};