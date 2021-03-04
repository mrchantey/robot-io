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
/*AUTO SCRIPT*/    public class Vector3MessageReceiver : MessageReceiver<Vector3>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public Vector3UnityEvent onMessage;
/*AUTO SCRIPT*/        protected override void HandleMessage(Message<Vector3> msg)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            onMessage.Invoke(msg.data[0]);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}