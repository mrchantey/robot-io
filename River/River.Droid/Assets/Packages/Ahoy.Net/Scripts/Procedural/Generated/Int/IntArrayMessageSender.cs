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
/*AUTO SCRIPT*/    // [CreateAssetMenu(fileName = "SendInt", menuName = "Ahoy.Net/Message Sender/Int", order = 0)]
/*AUTO SCRIPT*/    public class IntArrayMessageSender : MessageSender<int[]>
/*AUTO SCRIPT*/    {
/*AUTO SCRIPT*/        protected override byte[] GetBytes(int[] val)
/*AUTO SCRIPT*/        {
/*AUTO SCRIPT*/            return IntParse.EncodeToBytes(headerInfo.channel, headerInfo.command, val);
/*AUTO SCRIPT*/        }
/*AUTO SCRIPT*/    }
/*AUTO SCRIPT*/
/*AUTO SCRIPT*/}