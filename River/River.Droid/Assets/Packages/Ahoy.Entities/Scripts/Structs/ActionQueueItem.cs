using System;
using UnityEngine;

namespace Ahoy.Entities
{

    public struct ActionQueueItem
    {

        public float queueTime;
        public int queueFrame;
        public Action action;
        public string id;

        public ActionQueueItem(Action _action, string _id)
        {
            action = _action;
            id = _id;
            queueTime = Time.time;
            queueFrame = Time.frameCount;
        }

    }
}

