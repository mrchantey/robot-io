using UnityEngine;

namespace Ahoy
{

    public class MouseWorldSpaceController : MonoBehaviour
    {
        [Range(0, 10)]
        public float distance = 1;


        private void Update()
        {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            var pos = ray.origin + ray.direction * distance;
            transform.position = pos;
        }


    }

}