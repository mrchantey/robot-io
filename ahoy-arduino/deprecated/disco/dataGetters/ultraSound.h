#pragma once

class UltraSound : public DataGetterAction<ulong>
{
public:
private:
  const ulong PULSE_TIMEOUT = 10000; //equivelant to 343cm/2 = 171.5cm
  ubyte trigPin;
  ubyte echoPin;

public:
  UltraSound(ubyte _trigPin, ubyte _echoPin, bool autoRepeat = true) : DataGetterAction<ulong>(autoRepeat)
  {
    trigPin = _trigPin;
    echoPin = _echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  void Invoke(NoType noType)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    ulong duration = pulseIn(echoPin, HIGH, PULSE_TIMEOUT);
    //  float duration = pulseIn(echoPin,HIGH);
    ulong data = duration * 0.034 / 2;
    // Serial.println("invoked");

    // DataGetterAction<ulong>::onData->Invoke(data);
    onData->Invoke(data);
  }
};