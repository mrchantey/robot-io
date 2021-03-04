// #pragma once

// template <typename dataT>
// class FuncBase
// {
//   public:
//     virtual dataT Invoke() = 0;
// };

// template <typename instT, typename dataT>
// class Func : public FuncBase<dataT>
// {

//   public:
//     instT *instance;
//     dataT (instT::*invokeMethod)();

//     Func() {}
//     Func(instT *_instance, dataT (instT::*_invokeMethod)())
//     {
//         instance = _instance;
//         invokeMethod = _invokeMethod;
//     }

//     dataT Invoke()
//     {
//         return (*instance.*invokeMethod)();
//     }
// };