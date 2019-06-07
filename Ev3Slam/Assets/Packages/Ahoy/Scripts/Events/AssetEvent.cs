using UnityEngine;
using System.Collections.Generic;
namespace Ahoy
{

    [CreateAssetMenu(fileName = "AssetEvent", menuName = "Ahoy/AssetEvent", order = 0)]
    public class AssetEvent<ValueT, ListenerT> : ScriptableObject
    where ListenerT : UnityEngine.Events.UnityEvent<ValueT>
    {

        List<ListenerT> listeners = new List<ListenerT>();

        public void AddListener(ListenerT listener)
        {
            if (!listeners.Contains(listener))
                listeners.Add(listener);
        }
        public void RemoveListener(ListenerT listener)
        {
            if (listeners.Contains(listener))
                listeners.Remove(listener);
        }

        public void Invoke(ValueT val)
        {
            listeners.ToArray().ForEach(l => l.Invoke(val));
        }

    }

}