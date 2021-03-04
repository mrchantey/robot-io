

class MPUTransmitAction : public ActionBase<MPUData>
{

  public:
    void Invoke(MPUData data)
    {
        ubyte len = 12;
        ubyte msg[len];
        msg[0] = 23;
        ubyte timeStamp[4];
        Data::LongToBytes(LoopSystem::elapsedMillis, timeStamp);
        msg[1] = timeStamp[0];
        msg[2] = timeStamp[1];
        msg[3] = timeStamp[2];
        msg[4] = timeStamp[3];

        msg[5] = Data::MapUIntToUbyte(data.acc.x);
        msg[6] = Data::MapUIntToUbyte(data.acc.y);
        msg[7] = Data::MapUIntToUbyte(data.acc.z);
        msg[8] = Data::MapUIntToUbyte(data.gyro.x);
        msg[9] = Data::MapUIntToUbyte(data.gyro.y);
        msg[10] = Data::MapUIntToUbyte(data.gyro.z);
        msg[11] = Data::MapUIntToUbyte(data.temp);

        RadioTransmitter::Transmit(msg, len);
    }
};