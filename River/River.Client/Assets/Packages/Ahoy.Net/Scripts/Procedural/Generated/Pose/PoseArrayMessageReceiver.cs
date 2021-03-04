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
/*AUTO SCRIPT*/    public class PoseArrayMessageReceiver : MessageReceiver<Pose>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public PoseArrayUnityEvent onMessage;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        protected override void HandleMessage(Message<Pose> msg)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            onMessage.Invoke(msg.data);
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}