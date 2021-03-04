// using UnityEngine;

// namespace Ahoy.Net
// {

//     public class Messenger : InvocableMono
//     {

//         public StringMessage stringMessage;
//         public StringMessageUnityEvent stringMessageEvent;
//         // public Vec3Message message;
//         public string vec3MessageName;
//         public Vector3 vec3MessageValue;
//         public Vec3MessageUnityEvent vec3MessageEvent;

//         public override void Invoke()
//         {
//             if (stringMessage.name != "")
//                 stringMessageEvent.Invoke(stringMessage);
//             if (vec3MessageName != "")
//                 vec3MessageEvent.Invoke(new Vec3Message(new Vec3(vec3MessageValue), vec3MessageName));
//         }


//     }

// }