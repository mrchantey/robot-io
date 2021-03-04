using UnityEngine;
using UnityEngine.Events;
using System.Collections.Generic;
using System;
using System.Linq;


namespace Ahoy
{
    [CreateAssetMenu(fileName = "Gen010AssetEvent", menuName = "Ahoy/Asset Events/gen010", order = 0)]
    public class Gen010AssetEvent : InvocableSO
    {
        public bool debug;
        public string debugName = "gen010 Asset Event";
        public gen010 testValue;

        // public List<Gen010UnityEvent> listeners = new List<Gen010UnityEvent>();
        public List<Gen010UnityEvent> listeners;


        public void AddListener(Gen010UnityEvent listener)
        {
            listeners.TryAdd(listener);
        }
        public void RemoveListener(Gen010UnityEvent listener)
        {
            listeners.TryRemove(listener);
        }


        public void Invoke(gen010 val)
        {
            if (debug)
                Debug.Log($"{debugName} event invoked: {val}");
            listeners.ToArray().ForEach(l => l.Invoke(val));
        }

        public override void Invoke()
        {
            Invoke(testValue);
        }


    }
}