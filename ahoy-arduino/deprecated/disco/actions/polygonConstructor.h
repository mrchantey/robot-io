

class PolygonConstructor : public ActionBase<float>
{

public:
  uint numSides;
  float radius;
  ActionBase<float> *onData;

  PolygonConstructor(uint _numSides = 3, float _radius = 1)
  {
    numSides = _numSides;
    radius = _radius;
  }

  void Invoke(float theta)
  {
    Serial.print("theta: ");
    Serial.print(theta);
    Serial.print("\t");
    //the formula
    float newRad = cos(PI / 5) / cos((fmod(abs(theta), (TWO_PI / numSides))) - PI / numSides);
    newRad *= radius;
    onData->Invoke(newRad);
  }
};