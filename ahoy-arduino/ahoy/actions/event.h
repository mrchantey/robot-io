#pragma once

// #include "action.h"
// #include ""

const uint DEFAULT_ACTION_COUNT = 1;

template <typename dataT, uint ActionCount = DEFAULT_ACTION_COUNT>
class Event : public ActionBase<dataT>
{
public:
    ActionBase<dataT> *actions[ActionCount];
    int actionIndex = 0;

    void Invoke(dataT data)
    {
        for (int i = 0; i < ActionCount; i++)
        {
            if (actions[i] != NULL)
                actions[i]->Invoke(data);
        }
    }

    void AddAction(ActionBase<dataT> *action)
    {
        if (actionIndex >= ActionCount)
        {
#ifdef ARDUINO_DEBUG
            Serial.println("EVENT OVERFLOW");
#endif
        }
        else
        {
            actions[actionIndex++] = action;
        }
    }
};

template <uint ActionCount = DEFAULT_ACTION_COUNT>
class NullEvent : public ActionBase<NoType>
{
public:
    ActionBase<NoType> *actions[ActionCount];
    int actionIndex = 0;

    void Invoke(NoType data = noType)
    {
        for (int i = 0; i < ActionCount; i++)
        {
            if (actions[i] != NULL)
                actions[i]->Invoke(noType);
        }
    }

    void AddAction(ActionBase<NoType> *action)
    {
        if (actionIndex >= ActionCount)
        {
#ifdef ARDUINO_DEBUG
            Serial.println("EVENT OVERFLOW");
#endif
        }
        else
        {
            actions[actionIndex++] = action;
        }
    }
};
