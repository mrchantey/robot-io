// using UnityEngine;
// using Unity.Networking.Transport;
// using Unity.Entities;
// using Unity.Collections;
// using System;
// using System.IO;
// using System.Runtime.Serialization;
// using System.Runtime.Serialization.Formatters.Binary;

// namespace Ahoy.Net
// {

//     public static class Messaging
//     {
//         public static byte[] ObjectToBytes(object obj)
//         {
//             if (obj == null)
//                 return null;
//             BinaryFormatter bf = new BinaryFormatter();
//             using (var ms = new MemoryStream())
//             {
//                 bf.Serialize(ms, obj);
//                 return ms.ToArray();
//             }
//         }
//         public static object BytesToObject(byte[] bytes)
//         {
//             BinaryFormatter bf = new BinaryFormatter();
//             using (var ms = new MemoryStream())
//             {
//                 ms.Write(bytes, 0, bytes.Length);
//                 ms.Seek(0, SeekOrigin.Begin);
//                 return bf.Deserialize(ms);
//             }
//         }
//         public static T BytesToObject<T>(byte[] bytes)
//         {
//             return (T)BytesToObject(bytes);
//         }


//         public static Message ReadMessage(DataStreamReader stream)
//         {
//             var readerCtx = default(DataStreamReader.Context);
//             var messageLength = stream.ReadUInt(ref readerCtx);
//             // Debug.Log($"reading message of length {messageLength}");
//             byte[] bytes = stream.ReadBytesAsArray(ref readerCtx, (int)messageLength);
//             // Debug.Log($"message read");
//             var obj = BytesToObject(bytes);

//             if (obj.GetType() == typeof(Message))
//                 return (Message)obj;
//             else
//             {
//                 Debug.LogWarning($"object sent is not a message: {obj.GetType()}");
//                 return null;
//             }
//         }




//         public static void WriteMessage(Message message, Action<DataStreamWriter> sendCallback)
//         {
//             var bytes = ObjectToBytes(message);
//             // Debug.Log($"heres my bytes: {bytes.Length}\n{bytes.ElementsToString()}");
//             var totalLen = bytes.Length + sizeof(uint);
//             using (var writer = new DataStreamWriter(totalLen, Allocator.Temp))
//             {
//                 writer.Write((uint)bytes.Length);
//                 writer.Write(bytes, bytes.Length);
//                 sendCallback(writer);
//             }
//         }
//     }

// }