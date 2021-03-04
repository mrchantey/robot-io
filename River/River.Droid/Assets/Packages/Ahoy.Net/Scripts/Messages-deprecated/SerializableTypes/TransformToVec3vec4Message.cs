// using UnityEngine;

// namespace Ahoy.Net
// {

//     public class TransformToVec3vec4Message : InvocableMono
//     {
//         public string messageName = "transformPoseUpdate";
//         public Vec3vec4MessageUnityEvent onUpdate;
//         public override void Invoke()
//         {
//             var pose = new vec3vec4(transform.position, transform.rotation);
//             onUpdate.Invoke(new Vec3vec4Message(pose, messageName));
//         }

//     }

// }