

class YPRNormalizer : public ActionBase<IMUData>
{

  public:
    ActionBase<float> *onData;
    YPRNormalizer()
    {
    }
    void Invoke(IMUData data)
    {
        // Serial.println("received data");
        const int PI_AMP = PI * 10000;
        int valY = map(data.ypr.y(), -PI_AMP, PI_AMP, 0, 255);
        // int val = data.ypr.y();
        Serial.println(valY);
        // Vec<float, 3> val = data.ypr.Map<float>(-PI_AMP, PI_AMP, 0, 1);
        // String str = String() + "x: " + val.val[0] + "\ty: " + val.val[1] + "\tz: " + val.val[2];
        // Serial.println(str);
        // val.Print("ypr: ", "\r\n");
        // onData->Invoke()
    }
};
IMU<IMU_MPU6050> *mpu;
YPRNormalizer *normalizer;

void setup()
{

    Serial.begin(115200);
    while (Serial.available() && Serial.read())
        ;
    mpu = new IMU<IMU_MPU6050>();
    normalizer = new YPRNormalizer();
    mpu->onData = normalizer;
}