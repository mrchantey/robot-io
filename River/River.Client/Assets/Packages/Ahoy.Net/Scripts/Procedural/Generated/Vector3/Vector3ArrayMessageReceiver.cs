//
//
//	THS FILE IS AUTO GENERATED
//	DO NOT EDIT DIRECTLY
//
/*AUTO SCRIPT*/using UnityEngine;
/*AUTO SCRIPT*/using Unity.Entities;
/*AUTO SCRIPT*/namespace Ahoy.Net
/*AUTO SCRIPT*/{
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/    public class Vector3ArrayMessageReceiver : MessageReceiver<Vector3>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public Vector3ArrayUnityEvent onMessage;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        protected override void HandleMessage(Message<Vector3> msg)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            onMessage.Invoke(msg.data);
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}