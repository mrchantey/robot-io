

class Animator
{

  public:
    TimeLapseAction *timeLapseAction;
    LoopAction *loopAction;
    ReverseAction<float> *reverseAction;
    SinusoidLerpAction<float> *sinAction;
    ActionBase<float> *animAction;

  private:
  public:
    // DataLogger<float> *rawLogger;
    // DataLogger<float> *sinLogger;
    // Logger *loopLogger;

    Animator(ActionBase<float> *_animAction, bool debug = true)
    {
        animAction = _animAction;

        timeLapseAction = new TimeLapseAction();

        loopAction = new LoopAction();
        timeLapseAction->onEnd->AddAction(loopAction);
        loopAction->onLoop->AddAction(timeLapseAction->doReset);

        reverseAction = new ReverseAction<float>();
        timeLapseAction->onUpdate->AddAction(reverseAction);
        loopAction->onLoop->AddAction(reverseAction->doToggleReverse);

        sinAction = new SinusoidLerpAction<float>();
        reverseAction->onData->AddAction(sinAction);

        sinAction->onData->AddAction(_animAction);

        if (debug)
        {
            // LoopSystem::doPrint = false;
            timeLapseAction->onUpdate->AddAction(new DataLogger<float>("raw data: "));
            reverseAction->onData->AddAction(new DataLogger<float>("reverse data: "));
            sinAction->onData->AddAction(new DataLogger<float>("sinusoid data: ", true));
            loopAction->onLoop->AddAction(new Logger("A LOOP OCCURED", true));
        }
    }

    void Start()
    {
        loopAction->Reset();
        timeLapseAction->Start();
    }
};