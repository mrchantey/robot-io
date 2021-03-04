// using UnityEngine;

// namespace Ahoy.Net
// {

//     public class MessageParser : MonoBehaviour
//     {
//         public bool debug;

//         public NullMessageUnityEvent nullMessage;
//         public ObjectMessageUnityEvent objectMessage;
//         public BoolMessageUnityEvent boolMessage;
//         public StringMessageUnityEvent stringMessage;
//         public FloatMessageUnityEvent floatMessage;
//         public IntMessageUnityEvent intMessage;
//         public ObjectArrayMessageUnityEvent objectArrayMessage;
//         public BoolArrayMessageUnityEvent boolArrayMessage;
//         public StringArrayMessageUnityEvent stringArrayMessage;
//         public FloatArrayMessageUnityEvent floatArrayMessage;
//         public IntArrayMessageUnityEvent intArrayMessage;
//         public Vec2MessageUnityEvent vec2Message;
//         public Vec2ArrayMessageUnityEvent vec2ArrayMessage;
//         public Vec3MessageUnityEvent vec3Message;
//         public Vec3ArrayMessageUnityEvent vec3ArrayMessage;


//         public void ParseMessage(Message msg)
//         {
//             if (debug)
//                 Debug.Log($"message parser - {msg}");
//             switch (msg.messageType)
//             {
//                 case MessageType.Null:
//                     nullMessage.Invoke((NullMessage)msg);
//                     break;
//                 case MessageType.Object:
//                     objectMessage.Invoke((ObjectMessage)msg);
//                     break;
//                 case MessageType.Bool:
//                     boolMessage.Invoke((BoolMessage)msg);
//                     break;
//                 case MessageType.String:
//                     stringMessage.Invoke((StringMessage)msg);
//                     break;
//                 case MessageType.Int:
//                     intMessage.Invoke((IntMessage)msg);
//                     break;
//                 case MessageType.Float:
//                     floatMessage.Invoke((FloatMessage)msg);
//                     break;
//                 case MessageType.Vec2:
//                     vec2Message.Invoke((Vec2Message)msg);
//                     break;
//                 case MessageType.Vec3:
//                     vec3Message.Invoke((Vec3Message)msg);
//                     break;
//                 case MessageType.ObjectArray:
//                     objectArrayMessage.Invoke((ObjectArrayMessage)msg);
//                     break;
//                 case MessageType.BoolArray:
//                     boolArrayMessage.Invoke((BoolArrayMessage)msg);
//                     break;
//                 case MessageType.StringArray:
//                     stringArrayMessage.Invoke((StringArrayMessage)msg);
//                     break;
//                 case MessageType.IntArray:
//                     intArrayMessage.Invoke((IntArrayMessage)msg);
//                     break;
//                 case MessageType.FloatArray:
//                     floatArrayMessage.Invoke((FloatArrayMessage)msg);
//                     break;
//                 case MessageType.Vec2Array:
//                     vec2ArrayMessage.Invoke((Vec2ArrayMessage)msg);
//                     break;
//                 case MessageType.Vec3Array:
//                     vec3ArrayMessage.Invoke((Vec3ArrayMessage)msg);
//                     break;
//             }
//             // Debug.Log($"parsing message {}");
//         }


//     }

// }
// // if (msg.messageType == null)
// // else if (msg.GetType() == typeof(string))
// //     stringMessage.Invoke((string)msg);
// // else if (msg.GetType() == typeof(bool))
// //     boolMessage.Invoke((bool)msg);
// // else if (msg.GetType() == typeof(int))
// //     intMessage.Invoke((int)msg);
// // else if (msg.GetType() == typeof(Vector3Message))
// //     vector3Message.Invoke(((Vector3Message)msg).ToVector3());
// // else if (msg.GetType() == typeof(Vector3Message[]))
// //     vector3ArrayMessage.Invoke(Vector3Message.ToVector3(((Vector3Message[])msg)));
// // else if (msg.GetType() == typeof(int[]))
// //     intArrayMessage.Invoke((int[])msg);
// // else
// //     objectMessage.Invoke(obj);