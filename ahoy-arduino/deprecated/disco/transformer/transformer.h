#pragma once

#include "animatedEyes.h"
#include "proximityDetector.h"

class Transformer
{

public:
  ProximityDetector *proximityDetector;
  AnimatedEyes *animatedEyes;

public:
  Transformer()
  {
    Serial.println("tranformer created");
    animatedEyes = new AnimatedEyes();
    proximityDetector = new ProximityDetector();

    proximityDetector->dataMonitor->valueChangeAction->onChange->AddAction(animatedEyes->doAwaken);
  }
};