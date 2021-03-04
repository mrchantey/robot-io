

class Data
{

  public:
    static void LongToBytes(long val, ubyte bytes[])
    {
        bytes[0] = ((val >> 24) & 0xFF);
        bytes[1] = ((val >> 16) & 0xFF);
        bytes[2] = ((val >> 8) & 0xFF);
        bytes[3] = ((val >> 0) & 0xFF);
    }

    static ulong BytesToUlong(ubyte bytes[])
    {
        ulong a = (ulong)bytes[0] << 24;
        ulong b = (ulong)bytes[1] << 16;
        ulong c = (ulong)bytes[2] << 8;
        ulong d = (ulong)bytes[3] << 0;
        return a + b + c + d;
        // return ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + (bytes[3] << 0));
    }

    static ubyte MapUIntToUbyte(uint val)
    {
        return (float)val / 65535 * 255;
    }

    static String ConvertToBits(ubyte *byteArr, uint len)
    {
        // ubyte len = str.length();

        // ubyte byteArr[len];
        // for (int i = 0; i < len; i++)
        // {
        //     byteArr[i] = str[i];
        // }

        ubyte charLen = len * 8 + 1;
        char bitArr[charLen];
        bitArr[charLen - 1] = '\0';

        for (int valIndex = 0; valIndex < len; valIndex++)
        {
            ubyte bitArrayIndex = valIndex * 8;
            ubyte a = byteArr[valIndex];
            for (int bitIndex = 7; bitIndex >= 0; bitIndex--)
            {
                ubyte i = bitArrayIndex + bitIndex;
                bitArr[i] = a % 2 == 0 ? '0' : '1';
                a /= 2;
            }
        }
        return String(bitArr);
    }
};