#pragma once

#include "../disco.h"

class Transformer
{

  public:
    Action<Transformer, NoType> *goToSleep;

    ColorLight *leftEye;
    ColorLight *rightEye;
    HueAnimAction *animAction;
    AnimCycle *cycle;
    UltraSound *ultraSound;
    DataAnalyzer<ulong> *ultraSoundAnalyzer;
    Action<Transformer, ulong> *onUltraSoundChange;

  private:
    bool isAwake = false;

  public:
    Transformer()
    {
        Serial.println("tranformer created");
        goToSleep = new Action<Transformer, NoType>(this, &Transformer::GoToSleep);

        onUltraSoundChange = new Action<Transformer, ulong>(this, &Transformer::OnUltraSoundChange);
        ultraSound = new UltraSound(4, 2);
        ultraSoundAnalyzer = new DataAnalyzer<ulong>(ultraSound->getDataFunc);
        // ultraSoundAnalyzer->onChange = new DataLoggerAction<ulong>();
        ultraSoundAnalyzer->onChange = onUltraSoundChange;

        //light
        leftEye = new ColorLight(9, 10, 11);
        rightEye = new ColorLight(3, 5, 6);
        leftEye->Blink(100);
        rightEye->Blink(100);
        // Action<ColorLight, Color> *action = new Action<ColorLight, Color>(leftEye, &ColorLight::SetColor);
        Action<ColorLight, Color> *actionLeft = new Action<ColorLight, Color>(leftEye, &ColorLight::SetColor);
        Action<ColorLight, Color> *actionRight = new Action<ColorLight, Color>(rightEye, &ColorLight::SetColor);
        ActionArray<Color, 2> *setEyes = new ActionArray<Color, 2>();
        setEyes->actions[0] = actionLeft;
        setEyes->actions[1] = actionRight;

        // animAction = new HueAnimAction(action);
        animAction = new HueAnimAction(setEyes);
        cycle = new AnimCycle(animAction);
        GoToSleep();
    }

    void OnUltraSoundChange(ulong data)
    {
        Serial.print("ultrasound changed: ");
        Serial.println(data);
        if (!isAwake)
            WakeUp();
    }

    void GoToSleep()
    {
        isAwake = false;
        Serial.println("going to sleep");
        animAction->startHue = 0.04;
        animAction->endHue = 0.06;
        cycle->infinite = true;
        cycle->Start(3000);
    }

    void WakeUp()
    {
        isAwake = true;
        Serial.println("waking up");
        animAction->startHue = 0.2;
        animAction->endHue = 0.8;
        cycle->numLoops = 6;
        cycle->infinite = false;
        cycle->endListener = goToSleep;
        cycle->Start(1000);
    }

    void Update()
    {
        ultraSoundAnalyzer->Update();
        cycle->Update();
    }

    void Print()
    {
    }
};