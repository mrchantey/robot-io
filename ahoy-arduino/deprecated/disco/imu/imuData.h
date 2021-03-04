#pragma once

class IMUData
{
  public:
    Vec3Int acc;         //g-force
    Vec3Int euler;       //radians
    Vec3Int gravity;     //g-force
    Vec3Int ypr;         //radians
    Vec3Int accLin;      //g-force
    Vec3Int accLinWorld; //g-force
    IMUData()
    {
    }
    IMUData(Vec3Int _acc, Vec3Int _euler, Vec3Int _gravity, Vec3Int _ypr, Vec3Int _accLin, Vec3Int _accLinWorld)
    {
        acc = _acc;                 //g-force
        euler = _euler;             //radians
        gravity = _gravity;         //g-force
        ypr = _ypr;                 //radians
        accLin = _accLin;           //g-force
        accLinWorld = _accLinWorld; //g-force
    }

    static IMUData FromI2CDevLib(Vec3Int _acc, Vec3Int _euler, Vec3Int _gravity, Vec3Int _ypr, Vec3Int _accLin, Vec3Int _accLinWorld)
    {
        return IMUData(_acc, _euler, _gravity, _ypr, _accLin, _accLinWorld);
    }

    void Print()
    {
        acc.Print("acc:\t");
        euler.Print("euler:\t");
        gravity.Print("gravity:\t");
        ypr.Print("ypr:\t");
        accLin.Print("accLin:\t");
        accLinWorld.Print("accLinWorld:\t", "\r\n");
    }

    String ToString()
    {
    }
    String ToJson()
    {
    }

    Vec3Float GetEulerRadians()
    {
        return Vec3Float(
            (float)euler.x() - 10000,
            (float)euler.y() - 10000,
            (float)euler.z() - 10000);
    }

    // String ToString()
    // {
    //     // return String("") + "acc: " + acc.ToString() + "\tgyro: " + gyro.ToString() + "\ttemp: " + temp;
    // }

    // String ToJson()
    // {
    //     // return acc.ToJson();
    //     // return String("") + "{\"acc\":" + acc.ToJson() + ",\"gyro\":" + gyro.ToJson() + ",\"temp\":" + temp + "}";
    //     // return String("") + ",\"gyro\":" + gyro.ToJson() + "}"; // + ",\"temp\":" + temp + "}";
    // }

    // String ToRobotIOJson
};