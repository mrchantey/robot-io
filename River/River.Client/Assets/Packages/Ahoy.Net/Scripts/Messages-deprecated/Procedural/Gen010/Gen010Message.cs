// using UnityEngine;
// using System;
// using UnityEngine.Events;

// namespace Ahoy.Net
// {

//     [Serializable]
//     public class Gen010MessageUnityEvent : UnityEvent<Gen010Message> { }
//     [Serializable]
//     public class Gen010ArrayMessageUnityEvent : UnityEvent<Gen010ArrayMessage> { }
//     [Serializable]
//     public class Gen010Message : MessageBase<gen010>
//     {
//         public override MessageType messageType { get { return MessageType.Gen010; } }
//         public Gen010Message(gen010 _value, string _name) : base(_value, _name) { }
//         public Gen010Message(gen010 _value) : base(_value) { }
//     }
//     [Serializable]
//     public class Gen010ArrayMessage : MessageArray<gen010>
//     {
//         public override MessageType messageType { get { return MessageType.Gen010Array; } }

//         public Gen010ArrayMessage(gen010[] _value, string _name) : base(_value, _name) { }
//         public Gen010ArrayMessage(gen010[] _value) : base(_value) { }


//         public static Gen010ArrayMessage[] CreateArrayMessages(gen010[] arr, string name, int maxChunkSize = 32)
//         {
//             var chunks = arr.ToChunks(maxChunkSize);
//             var numChunks = chunks.GetLength(0);
//             var messages = new Gen010ArrayMessage[numChunks];
//             for (int i = 0; i < numChunks; i++)
//             {
//                 messages[i] = new Gen010ArrayMessage(chunks[i], name);
//             }
//             return messages;
//         }
//     }
// }