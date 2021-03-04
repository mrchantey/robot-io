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
/*AUTO SCRIPT*/    public class PoseMessageReceiver : MessageReceiver<Pose>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/        public PoseUnityEvent onMessage;
/*AUTO SCRIPT*/        protected override void HandleMessage(Message<Pose> msg)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            onMessage.Invoke(msg.data[0]);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}