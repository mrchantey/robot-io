// using UnityEngine;

// namespace Ahoy.Net
// {

//     public class Vec4ArrayMessageCaster : MonoBehaviour
//     {

//         public Vector4ArrayUnityEvent onInvokeVector4;
//         public QuaternionArrayUnityEvent onInvokeQuaternion;

//         public void Invoke(Vec4ArrayMessage msg)
//         {
//             onInvokeVector4.Invoke(msg.value.ToVector4());
//             onInvokeQuaternion.Invoke(msg.value.ToQuaternion());
//         }

//     }

// }