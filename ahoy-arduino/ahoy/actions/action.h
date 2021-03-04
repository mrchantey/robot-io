#pragma once

// #include "../disco.h"

template <typename dataT>
class ActionBase
{
public:
  virtual void Invoke(dataT data) = 0;
};

template <typename dataT>
class StaticAction : public ActionBase<dataT>
{

private:
  void (*invokeAction)(dataT);

public:
  StaticAction(void (*_invokeAction)(dataT))
  {
    invokeAction = _invokeAction;
  }

  void Invoke(dataT data)
  {
    invokeAction(data);
  }
};

class StaticNullAction : public ActionBase<NoType>
{

private:
  void (*invokeAction)();

public:
  StaticNullAction(void (*_invokeAction)())
  {
    invokeAction = _invokeAction;
  }

  void Invoke(NoType nt = noType)
  {
    invokeAction();
  }
};

template <typename instT, typename dataT>
class Action : public ActionBase<dataT>
{

private:
  instT *instance;
  void (instT::*invokeAction)(dataT);

public:
  Action(instT *_instance, void (instT::*_invokeAction)(dataT))
  {
    instance = _instance;
    invokeAction = _invokeAction;
  }
  void Invoke(dataT data)
  {
    (*instance.*invokeAction)(data);
  }
};

template <typename instT>
class NullAction : public ActionBase<NoType>
{
private:
  instT *instance;
  void (instT::*invokeAction)();

public:
  NullAction(instT *_instance, void (instT::*_invokeAction)())
  {
    instance = _instance;
    invokeAction = _invokeAction;
  }

  void Invoke(NoType data = noType)
  {
    (*instance.*invokeAction)();
  }
};
