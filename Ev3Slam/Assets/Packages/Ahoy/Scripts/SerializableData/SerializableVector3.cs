using UnityEngine;
using System.Linq;
namespace Ahoy
{
    [System.Serializable]
    public struct SerializableVector3
    {
        public float x;
        public float y;
        public float z;

        public SerializableVector3(Vector3 vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }

        public Vector3 ToVector3()
        {
            return new Vector3(x, y, z);
        }
        public static Vector3[] ToVector3(SerializableVector3[] vecs)
        {
            return vecs.Select(v => v.ToVector3()).ToArray();
        }

        public static SerializableVector3[] ToSerializableVector3(Vector3[] vecs)
        {
            return vecs.Select(v => new SerializableVector3(v)).ToArray();
        }

    }

}