
MPU6050 *mpu;

MPUPhysicsAction *action;

void setup()
{
    Serial.begin(115200);
    mpu = new MPU6050();
    action = new MPUPhysicsAction();
    mpu->onData = action;
}