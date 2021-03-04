
// LoggerAction *logAction;
// AnimAction<NoType> *animAction;

HueAnimAction *animAction;
TimeLapseAction *timeAction;
// SinusoidLerpAction<float> sinAction;

ColorLogger *logger;

ColorLight *leftEye;

void setup()
{
    Serial.begin(115200);
    timeAction = new TimeLapseAction();

    animAction = new HueAnimAction();
    timeAction->onUpdate->AddAction(animAction);

    logger = new ColorLogger(true);
    animAction->onData->AddAction(logger);

    leftEye = new ColorLight(9, 10, 11);
    animAction->onData->AddAction(leftEye->doSetColor);

    timeAction->Start();
}
