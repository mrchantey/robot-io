//
//
//	THS FILE IS AUTO GENERATED
//	DO NOT EDIT DIRECTLY
//
/*AUTO SCRIPT*/using Unity.Entities;
/*AUTO SCRIPT*/using UnityEngine;
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/namespace Ahoy.Net
/*AUTO SCRIPT*/{
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/    // [CreateAssetMenu(fileName = "SendVector3", menuName = "Ahoy.Net/Message Sender/Vector3", order = 0)]
/*AUTO SCRIPT*/    public class Vector2MessageSender : MessageSender<Vector2>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/        protected override byte[] GetBytes(Vector2 val)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            return Vector2Parse.EncodeToBytes(headerInfo.channel, headerInfo.command, val);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}