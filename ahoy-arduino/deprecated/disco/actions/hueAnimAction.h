#pragma once

class HueAnimAction : public ActionBase<float>
{
  public:
    float startHue;
    float endHue;
    ActionArray<Color> *onData;

    HueAnimAction(float _startHue = 0, float _endHue = 0.5)
    {
        startHue = _startHue;
        endHue = _endHue;
        onData = new ActionArray<Color>();
    }

    void Invoke(float t)
    {
        float hue = Math::Lerp(startHue, endHue, t);
        Color col = Color::FromHSV(hue, 1, 1);
        onData->Invoke(col);
    }
};