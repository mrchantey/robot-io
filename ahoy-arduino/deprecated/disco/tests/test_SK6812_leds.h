
class StripUpdater
{
public:
    LedStripBase<CRGBW> *strip;
    Action<StripUpdater, NoType> *doUpdate;
    StripUpdater(LedStripBase<CRGBW> *_strip)
    {
        strip = _strip;
        doUpdate = new Action<StripUpdater, NoType>(this, &StripUpdater::Update);
    }

    float incr = 0;
    void Update()
    {
        incr = fmod(incr + 0.01, 1);
        ubyte r = 0;
        ubyte g = 255;
        ubyte b = 127;
        ubyte w = 0;

        // ubyte val1 = 255;
        // ubyte val2 = 0;
        // ubyte val3 = 255;
        // ubyte val4 = 0;

        // uint freq = map(analogRead(A0),0,1023,0,)
        uint freq = analogRead(A0);
        CRGBW col1 = CRGBW(r, g, b, w);
        // CRGBW col1 = CRGBW(val1, val2, val3, val4);
        // CRGBW col2 = CRGBW(val3, val1, val2, val4);
        // CRGBW col3 = CRGBW(val2, val3, val1, val4);
        // CRGBW col1 = CRGBW(val1,val2,val3,val4);
        strip->SetAllLeds(col1);
        // delay(freq);
        // strip->SetAllLeds(col2);
        // delay(freq);
        // strip->SetAllLeds(col3);
        // delay(freq);
        // strip->SetFromNormal(incr, CRGBW(0, 32, 32, 16));
        // strip->SetFromNormal(incr, CRGBW(0, 0, 0, 0));
    }
};

const int numLeds = 115;

RgbwLedStrip<3, numLeds> *ledStrip;
StripUpdater *updater;

void setup()
{
    pinMode(A0, INPUT);
    ledStrip = new RgbwLedStrip<3, numLeds>();
    ledStrip->SetAllLeds(CRGBW(0, 0, 0, 0));
    updater = new StripUpdater(ledStrip);
    LoopSystem::AddListener(updater->doUpdate);
}
