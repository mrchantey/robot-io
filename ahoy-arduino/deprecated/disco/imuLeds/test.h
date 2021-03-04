const int numLeds = 60;
RgbwLedStrip<3, numLeds> *ledStrip;

IMU_MPU6050 *imu;
void setup()
{
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    Serial.begin(115200);
    // Serial.println("initializing");
    while (Serial.available() && Serial.read())
        ;
    Serial.println("initializing");
    ledStrip = new RgbwLedStrip<3, numLeds>();
    imu = new IMU_MPU6050();
    while (true)
    {
        IMUData data = imu->GetImuData();
        const int PI_AMP = PI * 10000;
        int valY = map(data.ypr.y(), -PI_AMP, PI_AMP, 0, 255);
        Serial.println(valY);
        int sat = map(analogRead(A0), 0, 1024, 0, 255);
        int value = map(analogRead(A1), 0, 1024, 0, 255);

        CHSV hsv = CHSV(valY, sat, value);
        CRGB rgb;
        hsv2rgb_rainbow(hsv, rgb);
        CRGBW rgbw = CRGBW(rgb.r, rgb.g, rgb.b, 0);

        ledStrip->SetAllLeds(rgbw);
    }
}