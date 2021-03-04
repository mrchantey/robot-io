using UnityEngine;

namespace Ahoy.Navigation
{

    public class TransformMover : MonoBehaviour
    {
        [Range(0, 16)]
        public float speed = 3;
        [Range(0, 64)]
        public float rotationSpeed = 32;

        public void Translate(float scalar)
        {
            Vector3 translation = Vector3.forward * speed * Time.deltaTime * scalar;
            transform.Translate(translation, Space.Self);
        }
        public void Rotate(float scalar)
        {
            var rotation = Vector3.up * rotationSpeed * Time.deltaTime * scalar;
            transform.Rotate(rotation, Space.Self);
        }
    }

}