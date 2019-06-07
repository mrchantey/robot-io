using UnityEngine;
using Unity.Entities;
using Unity.Collections;
using Unity.Jobs;

using System;
using System.Collections.Generic;

namespace Ahoy.Entities
{

    public class TestActionQueueSystem : InvocableMono
    {

        ActionQueueData data;
        public int numActions = 3;
        public int frameModulo = 3;
        public int maxDispatchesPerFrame = 3;

        protected override void Start()
        {
            Init();
        }

        void Init()
        {
            var manager = World.Active.EntityManager;
            var actionQueueSystem = World.Active.GetOrCreateSystem<ActionQueueSystem>();
            data = new ActionQueueData("my queue");
            data.frameModulo = frameModulo;
            data.maxDispatchesPerUpdate = maxDispatchesPerFrame;
            data.debug = true;
            data.debugFull = true;
            actionQueueSystem.CreateQueue(data);

        }

        public override void Invoke()
        {
            // TestAsyncActions();
            // TestAsyncFunctions();
            TestSerialJobQueue();
        }

        void TestAsyncActions()
        {
            var myActions = new Action[numActions];
            for (int i = 0; i < numActions; i++)
            {
                // myActio
                var ii = i;
                myActions[i] = () => { Debug.Log($"hello {ii}!"); };
            }
            Debug.Log($"starting on frame {Time.frameCount}");
            data.AddActionsAsync(myActions)
            .Then(() => Debug.Log($"all done on frame {Time.frameCount}"));
        }
        void TestAsyncFunctions()
        {
            var myActions = new Func<int>[numActions];
            for (int i = 0; i < numActions; i++)
            {
                // myActio
                var ii = i;
                myActions[i] = () => { return ii * 2; };
            }
            Debug.Log($"starting on frame {Time.frameCount}");
            data.AddFunctionsAsync<int>(myActions)
            .Then((values) => Debug.Log($"all done on frame {Time.frameCount}, the result is {values.ElementsToString()}"));
        }

        struct Job : IJob
        {
            public NativeCounter counter;
            public void Execute()
            {

                // counter.Increment();
                float a = 0;
                for (int i = 0; i < 100000; i++)
                {
                    a += Mathf.Sqrt(32230);
                }
                counter.Count += (int)a;
            }

        };


        void TestSerialJobQueue()
        {
            var counter = new NativeCounter(Allocator.Persistent);
            var handle = new JobHandle();
            var myActions = new Action[numActions];
            for (int i = 0; i < numActions; i++)
            {
                var job = new Job()
                {
                    counter = counter
                };
                myActions[i] = () => handle = job.Schedule(handle);
            }
            Debug.Log($"starting on frame {Time.frameCount}");
            data.AddActionsAsync(myActions)
            .Then(() =>
            {
                Debug.Log($"handle status: {handle.IsCompleted}");
                handle.Complete();
                Debug.Log($"all done on frame {Time.frameCount}, the result is {counter.Count}");
                counter.Dispose();
            });
        }


    }
}
