using System;
using UnityEngine;

namespace Ahoy
{
    // [ExecuteAlways]
    public abstract class InvocableMono : MonoBehaviour
    {

        public bool InvokeOnValidate;
        public bool InvokeOnStart;
        public bool InvokeOnUpdate;
        public bool InvokeOnNthFrame;
        public int nthFrame = 5;

        bool needsInvoking;

        protected virtual void OnValidate()
        {
            //many operations cannot be done on validate call
            if (!InvokeOnValidate)
                return;
            needsInvoking = true;
        }

        protected virtual void Start()
        {
            if (InvokeOnStart)
                Invoke();
        }

        protected virtual void Update()
        {
            if (needsInvoking)
            {
                needsInvoking = false;
                Invoke();
            }
            if (InvokeOnUpdate)
                Invoke();
            if (InvokeOnNthFrame && Time.frameCount == nthFrame)
                Invoke();
        }

        public abstract void Invoke();
    }


}