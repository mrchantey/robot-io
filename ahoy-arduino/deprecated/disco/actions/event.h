// #pragma once

// #include "disco.h"

// template <typename dataT>
// class EventBase
// {
//   public:
//     ActionBase<dataT> *action;
//     // EventSubscriberBase *subscriber;
// };

// template <typename callerT, typename dataT>
// class Event : public EventBase<dataT>
// {
//   public:
//     Event(callerT *_instance, bool (callerT::*_Predicate)(), dataT (callerT::*_ValueGetter)())
//     {
//         instance = _instance;
//         Predicate = _Predicate;
//         ValueGetter = _ValueGetter;
//     }
//     void Update()
//     {
//         bool hasTriggered = (*instance.*Predicate)();
//         if (hasTriggered && this->action != NULL)
//         {
//             dataT val = (*instance.*ValueGetter)();
//             this->action->Invoke(val);
//         }
//     }

//   private:
//     callerT *instance;
//     bool (callerT::*Predicate)();
//     dataT (callerT::*ValueGetter)();
// };

// template <typename callerT>
// class Event<callerT, NoType> : public EventBase<NoType>
// {
//   public:
//     Event(callerT *_instance, bool (callerT::*_Predicate)())
//     {
//         instance = _instance;
//         Predicate = _Predicate;
//     }
//     void Update()
//     {
//         bool hasTriggered = (*instance.*Predicate)();
//         if (hasTriggered && this->action != NULL)
//         {
//             this->action->Invoke(NoType());
//         }
//     }

//   private:
//     callerT *instance;
//     bool (callerT::*Predicate)();
// };