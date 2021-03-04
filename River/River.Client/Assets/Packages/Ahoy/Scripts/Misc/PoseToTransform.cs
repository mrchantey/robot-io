using UnityEngine;

namespace Ahoy
{

    public class PoseToTransform : MonoBehaviour
    {
        public new Transform transform;
        public void Invoke(Pose pose)
        {
            transform.position = pose.position;
            transform.rotation = pose.rotation;
        }

    }

}