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
/*AUTO SCRIPT*/    // [CreateAssetMenu(fileName = "SendFloat", menuName = "Ahoy.Net/Message Sender/Float", order = 0)]
/*AUTO SCRIPT*/    public class FloatArrayMessageSender : MessageSender<float[]>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/        protected override byte[] GetBytes(float[] val)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            return FloatParse.EncodeToBytes(headerInfo.channel, headerInfo.command, val);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}