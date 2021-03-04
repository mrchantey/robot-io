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
/*AUTO SCRIPT*/    [CreateAssetMenu(fileName = "GameObjectAssetEvent", menuName = "Ahoy/Asset Events/GameObject", order = 0)]
/*AUTO SCRIPT*/    public class GameObjectAssetEvent : InvocableSO
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/        public bool debug;
/*AUTO SCRIPT*/        public string debugName = "GameObject Asset Event";
/*AUTO SCRIPT*/        public GameObject testValue;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        // public List<GameObjectUnityEvent> listeners = new List<GameObjectUnityEvent>();
/*AUTO SCRIPT*/        public List<GameObjectUnityEvent> listeners;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public void AddListener(GameObjectUnityEvent listener)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            listeners.TryAdd(listener);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/        public void RemoveListener(GameObjectUnityEvent listener)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            listeners.TryRemove(listener);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public void Invoke(GameObject val)
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