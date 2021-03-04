//
//
//	THS FILE IS AUTO GENERATED
//	DO NOT EDIT DIRECTLY
//
/*AUTO SCRIPT*/using UnityEngine;
/*AUTO SCRIPT*/using UnityEngine.Events;
/*AUTO SCRIPT*/using System.Collections.Generic;
/*AUTO SCRIPT*/using System;
/*AUTO SCRIPT*/using System.Linq;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/namespace Ahoy
/*AUTO SCRIPT*/{
/*AUTO SCRIPT*/    [CreateAssetMenu(fileName = "Vector4AssetEvent", menuName = "Ahoy/Asset Events/Vector4", order = 0)]
/*AUTO SCRIPT*/    public class Vector4AssetEvent : InvocableSO
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/        public bool debug;
/*AUTO SCRIPT*/        public string debugName = "Vector4 Asset Event";
/*AUTO SCRIPT*/        public Vector4 testValue;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        // public List<Vector4UnityEvent> listeners = new List<Vector4UnityEvent>();
/*AUTO SCRIPT*/        public List<Vector4UnityEvent> listeners;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public void AddListener(Vector4UnityEvent listener)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            listeners.TryAdd(listener);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/        public void RemoveListener(Vector4UnityEvent listener)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            listeners.TryRemove(listener);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public void Invoke(Vector4 val)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            if (debug)
/*AUTO SCRIPT*/                Debug.Log($"{debugName} event invoked: {val}");
/*AUTO SCRIPT*/            listeners.ToArray().ForEach(l => l.Invoke(val));
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public override void Invoke()
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            Invoke(testValue);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/}