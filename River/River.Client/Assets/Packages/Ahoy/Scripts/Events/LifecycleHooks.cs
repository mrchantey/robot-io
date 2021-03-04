using UnityEngine;
using UnityEngine.Events;

namespace Ahoy
{

    public class LifecycleHooks : MonoBehaviour
    {

        // deprecated - bad practice, use ComponentSystems
        // public static AhoyEvent OnStart = new AhoyEvent();
        // public static AhoyEvent OnUpdate = new AhoyEvent();

        public UnityEvent onStart;
        public UnityEvent onUpdate;


        private void Start()
        {
            // OnStart.Invoke();
            onStart.Invoke();
        }

        private void Update()
        {
            // OnUpdate.Invoke();
            onUpdate.Invoke();
        }

    }

}