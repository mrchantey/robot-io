

RobotIOTransmitter<int> *transmitter;

void setup()
{
    Serial.begin(115200);
    RobotIOSystem::BeginInitTransmission();
    ubyte accChartId = RobotIOSystem::InitChart("Acceleration");
    ubyte gyroChartId = RobotIOSystem::InitChart("Gyroscope");
    // // Serial.println(accChartId);
    transmitter = RobotIOSystem::InitTransmitter<int>("x", accChartId);
    RobotIOSystem::EndInitTransmission();
    transmitter->UpdateData(millis());
    RobotIOSystem::TransmitData();
    // LoopSystem::AddListener(RobotIOSystem::doTransmitData);
}
