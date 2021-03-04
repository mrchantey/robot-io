

class MPURobotIOTransmitter : public ActionBase<MPUData>
{
  public:
  private:
    RobotIOTransmitter<int> *accX;
    RobotIOTransmitter<int> *accY;
    RobotIOTransmitter<int> *accZ;

    RobotIOTransmitter<int> *gyroX;
    RobotIOTransmitter<int> *gyroY;
    RobotIOTransmitter<int> *gyroZ;

  public:
    MPURobotIOTransmitter()
    {
        uint accChartId = RobotIOSystem::InitChart("Accelerometer");
        uint gyroChartId = RobotIOSystem::InitChart("Gyroscope");

        accX = RobotIOSystem::InitTransmitter<int>("x", accChartId);
        accY = RobotIOSystem::InitTransmitter<int>("y", accChartId);
        accZ = RobotIOSystem::InitTransmitter<int>("z", accChartId);
        gyroX = RobotIOSystem::InitTransmitter<int>("x", gyroChartId);
        gyroY = RobotIOSystem::InitTransmitter<int>("y", gyroChartId);
        gyroZ = RobotIOSystem::InitTransmitter<int>("z", gyroChartId);
    }

    void Invoke(MPUData data)
    {
        accX->UpdateData(data.acc.x);
        accY->UpdateData(data.acc.y);
        accZ->UpdateData(data.acc.z);
        gyroX->UpdateData(data.gyro.x);
        gyroY->UpdateData(data.gyro.y);
        gyroZ->UpdateData(data.gyro.z);
    }
};