#pragma once

// #include "disco.h"

class ColorLight
{
public:
  Action<ColorLight, Color> *doSetColor;

private:
  int pinR;
  int pinG;
  int pinB;
  Color currentColor;

public:
  ColorLight(int _pinR, int _pinG, int _pinB)
  {
    doSetColor = new Action<ColorLight, Color>(this, &ColorLight::SetColor);
    pinR = _pinR;
    pinG = _pinG;
    pinB = _pinB;
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
  }
  void Blink(int duration = 1000)
  {
    SetColor(255);
    delay(duration);
    SetColor(0);
    delay(duration);
  }
  void SetColor(byte val)
  {
    currentColor = Color(val, val, val);
    analogWrite(pinR, val);
    analogWrite(pinG, val);
    analogWrite(pinB, val);
  }
  void SetColor(Color _color)
  {
    currentColor = _color;
    analogWrite(pinR, _color.r);
    analogWrite(pinG, _color.g);
    analogWrite(pinB, _color.b);
  }
};