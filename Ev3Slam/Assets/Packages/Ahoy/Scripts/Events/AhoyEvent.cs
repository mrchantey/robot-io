using UnityEngine;
using System;
using System.Collections.Generic;
namespace Ahoy
{

    public class AhoyEvent<T>
    {

        List<Action<T>> listeners;
        List<Action<T>> listenersOneShot;

        public AhoyEvent()
        {
            listeners = new List<Action<T>>();
            listenersOneShot = new List<Action<T>>();
        }

        public void Invoke(T val)
        {
            listeners.ToArray().ForEach(l => l.Invoke(val));
            listenersOneShot.ToArray().ForEach(l => l.Invoke(val));
            listenersOneShot.Clear();
        }

        public void AddListener(Action<T> listener)
        {
            if (!listeners.Contains(listener))
                listeners.Add(listener);
        }

        public void RemoveListener(Action<T> listener)
        {
            if (listeners.Contains(listener))
                listeners.Remove(listener);
        }

        public void AddListenerOneShot(Action<T> listener)
        {
            if (!listenersOneShot.Contains(listener))
                listenersOneShot.Add(listener);
        }
        public void RemoveListenerOneShot(Action<T> listener)
        {
            if (listenersOneShot.Contains(listener))
                listenersOneShot.Remove(listener);
        }

    }
    public class AhoyEvent
    {


        List<Action> listeners;
        List<Action> listenersOneShot;

        public AhoyEvent()
        {
            listeners = new List<Action>();
            listenersOneShot = new List<Action>();
        }

        public void Invoke()
        {
            listeners.ToArray().ForEach(l => l.Invoke());
            listenersOneShot.ToArray().ForEach(l => l.Invoke());
            listenersOneShot.Clear();
        }

        public void AddListener(Action listener)
        {
            if (!listeners.Contains(listener))
                listeners.Add(listener);
        }
        public void RemoveListener(Action listener)
        {
            if (listeners.Contains(listener))
                listeners.Remove(listener);
        }
        public void AddListenerOneShot(Action listener)
        {
            if (!listenersOneShot.Contains(listener))
                listenersOneShot.Add(listener);
        }
        public void RemoveListenerOneShot(Action listener)
        {
            if (listenersOneShot.Contains(listener))
                listenersOneShot.Remove(listener);
        }

    }
}