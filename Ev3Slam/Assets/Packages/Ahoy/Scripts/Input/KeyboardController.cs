using UnityEngine;

namespace Ahoy
{

    public class KeyboardController : MonoBehaviour
    {


        [Range(0, 10)]
        public float speed = 1f;
        [Range(0, 10)]
        public float torque = 1f;
        [Range(0, 10)]
        public float scrollSpeed = 3f;
        private void Update()
        {
            Vector3 dir = Vector3.zero;
            if (Input.GetKey(KeyCode.W))
                dir.z += 1;
            if (Input.GetKey(KeyCode.S))
                dir.z -= 1;
            if (Input.GetKey(KeyCode.A))
                dir.x -= 1;
            if (Input.GetKey(KeyCode.D))
                dir.x += 1;
            dir.y = Input.mouseScrollDelta.y * scrollSpeed;
            Vector3 vel = dir * speed * Time.deltaTime;
            transform.Translate(vel, Space.Self);

            var rotDir = 0;
            if (Input.GetKey(KeyCode.Q))
                rotDir -= 1;
            if (Input.GetKey(KeyCode.E))
                rotDir += 1;
            var rotation = Vector3.up * rotDir * torque;
            transform.Rotate(rotation, Space.Self);
        }
    }

}