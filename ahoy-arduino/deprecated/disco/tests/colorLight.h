

ColorLight *light;
StaticAction<NoType> *action;
// double count;

class ColorChanger
{
  public:
    static void SetColor()
    {
        light->SetColor(255);
    }
};

void setup()
{
    action = new StaticAction<NoType>(&ColorChanger::SetColor);
    LoopSystem::AddListener(action);
    light = new ColorLight(9, 10, 11);
}
