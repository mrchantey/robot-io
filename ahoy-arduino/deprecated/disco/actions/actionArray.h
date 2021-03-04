#pragma once

// #include "action.h"
// #include ""

const uint DEFAULT_ACTION_COUNT = 2;

template <typename dataT, uint ActionCount = DEFAULT_ACTION_COUNT>
class ActionArray : public ActionBase<dataT>
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
            Serial.println("Error: actions added to array exceeds action count, try initializing with a larger action count");
        }
        else
        {
            actions[actionIndex++] = action;
        }
    }
};
