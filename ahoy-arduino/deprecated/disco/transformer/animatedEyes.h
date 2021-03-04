

class AnimatedEyes
{

  public:
    Animator *animator;
    HueAnimAction *animAction;
    ColorLight *leftEye;
    ColorLight *rightEye;
    Action<AnimatedEyes, NoType> *doSleep;
    Action<AnimatedEyes, NoType> *doAwaken;
    Action<AnimatedEyes, NoType> *onAnimationEnd;

    bool isAwake = false;

  private:
  public:
    AnimatedEyes(bool debug = false)
    {
        animAction = new HueAnimAction();
        animator = new Animator(animAction, debug);

        leftEye = new ColorLight(9, 10, 11);
        rightEye = new ColorLight(3, 5, 6);
        animAction->onData->AddAction(leftEye->doSetColor);
        animAction->onData->AddAction(rightEye->doSetColor);
        leftEye->Blink(100);
        rightEye->Blink(100);

        onAnimationEnd = new Action<AnimatedEyes, NoType>(this, &AnimatedEyes::OnAnimationEnd);
        animator->loopAction->onEnd->AddAction(onAnimationEnd);
        doSleep = new Action<AnimatedEyes, NoType>(this, &AnimatedEyes::Sleep);
        doAwaken = new Action<AnimatedEyes, NoType>(this, &AnimatedEyes::Awaken);
        // Sleep();
        Awaken();
    }

    void Sleep()
    {
        isAwake = false;
        float randMin = random(0, 2) * 0.1;
        float randMax = random(3, 5) * 0.1;
        animAction->startHue = randMin;
        animAction->endHue = randMax;
        animator->loopAction->infinite = true;
        animator->timeLapseAction->durationMillis = 30000;
        animator->Start();
    }

    void Awaken()
    {
        if (isAwake)
            return;
        isAwake = true;
        animator->loopAction->infinite = false;
        animator->loopAction->numLoops = 9;
        animator->timeLapseAction->durationMillis = 1500;
        //    Serial.println("waking up");

        float randMin = random(0, 2) * 0.1;
        float randMax = random(8, 10) * 0.1;
        animAction->startHue = randMin;
        animAction->endHue = randMax;

        //     cycle->endListener = goToSleep;
        //     cycle->Start(1000);
        animator->Start();
        // }
    }

    void OnAnimationEnd()
    {
        Sleep();
    }
};