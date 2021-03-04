using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;
using Unity.Jobs;
using System.Collections.Generic;
using System;
using System.Linq;

namespace Ahoy.Entities
{

    public class AsyncJobSystem : ComponentSystem
    {

        List<AsyncJobItem> items;

        protected override void OnCreate()
        {
            items = new List<AsyncJobItem>();
        }

        public Promise CompleteAsync(JobHandle handle)
        {
            var prom = new Promise();
            var item = new AsyncJobItem(handle, prom);
            items.Add(item);
            return prom;
        }

        //use this one for chaining
        public void CompleteAsync(JobHandle handle, Promise prom)
        {
            var item = new AsyncJobItem(handle, prom);
            items.Add(item);
        }

        protected override void OnUpdate()
        {
            var completedItems = items
            .Where(i => i.handle.IsCompleted)
            .ToArray();
            completedItems.ForEach(i =>
            {
                items.Remove(i);
                Complete(i);
            });
        }

        void Complete(AsyncJobItem item)
        {
            item.handle.Complete();
            item.promise.Resolve();
        }

        protected override void OnDestroy()
        {
            items.ForEach(Complete);
        }

    }
}