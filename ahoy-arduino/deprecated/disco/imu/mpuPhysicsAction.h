

class MPUPhysicsAction : public ActionBase<MPUData>
{

  public:
    // Vector3Int vel;
    long vel;
    long pos;
    // Vector3Int pos;
    // Vector3Int angle;

    MPUPhysicsAction()
    {
        vel = 0;
        pos = 0;
        // vel = Vector3Int();
        // pos = Vector3Int();
    }

    void Invoke(MPUData data)
    {
        char str[60];

        // vel += data.acc;
        int a = map(data.acc.z, -32768, 32767, -127, 127);

        vel += a;
        vel = constrain(vel, -1000, 1000);
        pos += vel;
        // pos = constrain(pos, -1000, 1000);

        // uint mappedAcc = map()

        // Vector3Int mappedAcc = Vector3Int::Map(data.acc, -32768, 32767, 0, 100);
        // Vector3Int mappedVel = Vector3Int::Map(vel, -32768, 32767, 0, 100);
        // Vector3Int mapped = Vector3Int.Map(vel,-32768,32767,0,100);
        // Vector3Int gyro = Vector3Int();

        // sprintf(str, "ax: %d\tay: %d\taz: %d\tgx: %d\tgy: %d\tgz: %d\r\n",
        // sprintf(str, "ax: %d\tay: %d\taz: %d\tvx: %d\tvy: %d\tvz: %d\r\n",
        sprintf(str, "az: %d\tvz: %d\tpz: %d\r\n",
                a,
                vel,
                pos);
        Serial.print(str);
        delay(100);
    }
};