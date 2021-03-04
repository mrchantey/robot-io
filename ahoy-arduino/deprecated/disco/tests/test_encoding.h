

void setup()
{

    Serial.begin(9600);

    Vector3Int myVec1 = Vector3Int(-30000, 891, 65191);
    Vector3Byte myVec2 = Vector3Byte(myVec1);

    String prnt = String("");
    prnt += "\tx1: ";
    prnt += myVec1.x;
    prnt += "\ty1: ";
    prnt += myVec1.y;
    prnt += "\tz1: ";
    prnt += myVec1.z;
    prnt += "\tx2: ";
    prnt += myVec2.x;
    prnt += "\ty2: ";
    prnt += myVec2.y;
    prnt += "\tz2: ";
    prnt += myVec2.z;

    Serial.println(prnt);

    // for (ulong i = 65535; i <= 65538; i++)
    // {
    //     // int i = 255;
    //     ulong val = i;
    //     ubyte bytes[4];
    //     Data::LongToBytes(val, bytes);
    //     ulong val2 = Data::BytesToUlong(bytes);
    //     String prnt = String("");
    //     prnt += "old: ";
    //     prnt += val;
    //     prnt += "\tnew: ";
    //     prnt += val2;
    //     prnt += "\tbytes: ";
    //     prnt += bytes[0];
    //     prnt += "\t";
    //     prnt += bytes[1];
    //     prnt += "\t";
    //     prnt += bytes[2];
    //     prnt += "\t";
    //     prnt += bytes[3];
    //     Serial.println(prnt);
    // }
}
