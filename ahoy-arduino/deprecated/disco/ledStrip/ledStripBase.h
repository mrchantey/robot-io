

template <typename colorType>
class LedStripBase
{

public:
protected:
public:
  virtual void SetFromNormal(float val, colorType col, bool render = true) = 0;

  virtual void SetLed(uint index, colorType col, bool render = true) = 0;

  virtual void SetAllLeds(colorType col, bool render = true) = 0;

  void Render()
  {
    FastLED.show();
  }
  // virtual void SetLed(uint index, colorType col) = 0;
};
