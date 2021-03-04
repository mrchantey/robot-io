#pragma once

// //TODO BaseEventSubscriber
// class EventSubscriberBase
// {
//   public:
//     virtual void Trigger()
//     {
//         // cout << "subscriber triggered";
//     }
// };

// //TODO TypedEventSubscriber
// template <typename T>
// class EventSubscriber : public EventSubscriberBase
// {

//   public:
//     EventSubscriber()
//     {
//     }

//     EventSubscriber(T *_instance, void (T::*_OnTrigger)())
//     {
//         instance = _instance;
//         OnTrigger = _OnTrigger;
//     }

//     void Init(T *_instance, void (T::*_OnTrigger)())
//     {
//         instance = _instance;
//         OnTrigger = _OnTrigger;
//     }
//     void Trigger()
//     {
//         (*instance.*OnTrigger)();
//     }

//   private:
//     T *instance;
//     void (T::*OnTrigger)();
// };
