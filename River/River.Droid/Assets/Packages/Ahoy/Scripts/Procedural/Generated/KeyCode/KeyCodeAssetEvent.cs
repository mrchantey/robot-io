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
/*AUTO SCRIPT*/    [CreateAssetMenu(fileName = "KeyCodeAssetEvent", menuName = "Ahoy/Asset Events/KeyCode", order = 0)]
/*AUTO SCRIPT*/    public class KeyCodeAssetEvent : InvocableSO
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/        public bool debug;
/*AUTO SCRIPT*/        public string debugName = "KeyCode Asset Event";
/*AUTO SCRIPT*/        public KeyCode testValue;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        // public List<KeyCodeUnityEvent> listeners = new List<KeyCodeUnityEvent>();
/*AUTO SCRIPT*/        public List<KeyCodeUnityEvent> listeners;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public void AddListener(KeyCodeUnityEvent listener)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            listeners.TryAdd(listener);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/        public void RemoveListener(KeyCodeUnityEvent listener)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            listeners.TryRemove(listener);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public void Invoke(KeyCode val)
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