

TimeLapseAction *timeLapseAction;
LoopAction *loopAction;
ReverseAction<float> *reverseAction;
SinusoidLerpAction<float> *sinAction;
ValueChangeAction<float> *changeAction;

DataLogger<float> *rawLogger;
DataLogger<float> *sinLogger;
DataLogger<float> *changeLogger;
Logger *loopLogger;

void setup()
{
    Serial.begin(115200);
    LoopSystem::doPrint = false;

    timeLapseAction = new TimeLapseAction();

    loopAction = new LoopAction(2);
    timeLapseAction->onEnd->AddAction(loopAction);

    reverseAction = new ReverseAction<float>();
    timeLapseAction->onUpdate->AddAction(reverseAction);
    rawLogger = new DataLogger<float>("raw data: ");
    // reverseAction->onData->AddAction(rawLogger);

    sinAction = new SinusoidLerpAction<float>();
    reverseAction->onData->AddAction(sinAction);
    sinLogger = new DataLogger<float>("sin data: ", true);
    // sinAction->onData->AddAction(sinLogger);

    changeAction = new ValueChangeAction<float>(0.1);
    sinAction->onData->AddAction(changeAction);
    changeLogger = new DataLogger<float>("CHANGE DATA:", true);
    changeAction->onChange->AddAction(changeLogger);

    loopLogger = new Logger("animation looping...");
    loopAction->onLoop->AddAction(reverseAction->doToggleReverse);
    loopAction->onLoop->AddAction(loopLogger);
    loopAction->onLoop->AddAction(new PrintLine());
    loopAction->onLoop->AddAction(timeLapseAction->doReset);

    // timeLapseAction->onUpdate->AddAction(logger);
    timeLapseAction->Start();
}