using System;
using UnityEngine;
using Unity.Jobs;

namespace Ahoy.Entities
{

    public struct AsyncJobItem
    {

        // public float queueTime;
        // public int queueFrame;
        public JobHandle handle;
        public Promise promise;
        // public string id;

        public AsyncJobItem(JobHandle _handle, Promise _promise)
        // public AsyncJobItem(JobHandle _handle, Promise _promise, string _id)
        {
            handle = _handle;
            promise = _promise;
            // id = _id;
            // queueTime = Time.time;
            // queueFrame = Time.frameCount;
        }

    }
}

