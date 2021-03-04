using UnityEngine;
using Unity.Entities;
using Unity.Collections;
using Unity.Jobs;

using System;
using System.Collections.Generic;

namespace Ahoy.Entities
{

    public class TestQueuedAsyncJobSystem : InvocableMono
    {


        ActionQueueData queueData;
        public int numJobs = 1;
        [Range(1, 8)]
        public int iterations = 7;
        public int frameModulo = 3;
        public int maxDispatchesPerFrame = 3;


        EntityManager manager;
        AsyncJobSystem asyncJobSystem;

        protected override void Start()
        {
            Init();
        }

        void Init()
        {
            manager = World.Active.EntityManager;
            asyncJobSystem = World.Active.GetOrCreateSystem<AsyncJobSystem>();

            var actionQueueSystem = World.Active.GetOrCreateSystem<ActionQueueSystem>();
            queueData = new ActionQueueData("my queue");
            queueData.frameModulo = frameModulo;
            queueData.maxDispatchesPerUpdate = maxDispatchesPerFrame;
            queueData.debug = true;
            queueData.debugFull = true;
            actionQueueSystem.CreateQueue(queueData);
        }

        public override void Invoke()
        {
            TestSerialAsyncJobQueue();
        }

        struct Job : IJob
        {
            public int iterations;
            // public NativeCounter counter;
            public void Execute()
            {

                // counter.Increment();
                long iter = 10;
                for (int i = 0; i < iterations; i++)
                {
                    iter *= 10;
                }
                // Debug.Log($"iterating {iter} times");
                float a = 0;
                for (int i = 0; i < iter; i++)
                {
                    a += Mathf.Sqrt(32230);

                }
                // counter.Count += (int)a;
            }
        };


        void TestSerialAsyncJobQueue()
        {
            var handle = new JobHandle();
            var actions = new Action[numJobs];
            var counter = new NativeCounter(Allocator.Persistent);
            var promises = new Promise[numJobs];

            for (int i = 0; i < numJobs; i++)
            {
                int ii = i;
                actions[i] = () =>
                {
                    var job = new Job()
                    {
                        // counter = counter,
                        iterations = iterations
                    };

                    handle = job.Schedule(handle);
                    // var newHandle = job.Schedule();
                    // handle = JobHandle.CombineDependencies(handle, newHandle);
                    Debug.Log($"<color=blue>job {ii} scheduled on frame {Time.frameCount}</color>");
                    promises[ii] = asyncJobSystem.CompleteAsync(handle);
                    //yea they are multiple promis callbacks not supported
                    promises[ii].Then(() =>
                    {
                        Debug.Log($"<color=green>job {ii} completed on frame {Time.frameCount}</color>");
                    });
                };
            }
            queueData.AddActionsAsync(actions)
            .Then(() =>
            {
                Debug.Log($"all jobs scheduled on frame {Time.frameCount}");
                Promise.All(promises)
                .Then(() =>
                {
                    Debug.Log($"handle complete status: {handle.IsCompleted}");
                    handle.Complete();
                    Debug.Log($"all done on frame {Time.frameCount}, the result is {counter.Count}");
                    counter.Dispose();
                });
            });
        }

        void TestChainedAsyncJobQueue()
        {
            var handle = new JobHandle();
            var actions = new Action[numJobs];
            var counter = new NativeCounter(Allocator.Persistent);
            var promises = new Promise[numJobs];

            for (int i = 0; i < numJobs; i++)
            {
                int iFixed = i;
                promises[i] = new Promise();
                promises[iFixed].Then(() =>
                {
                    Debug.Log($"<color=green>job {iFixed} completed on frame {Time.frameCount}</color>");
                });


                actions[i] = () =>
                {
                    var job = new Job()
                    {
                        // counter = counter,
                        iterations = iterations
                    };

                    handle = job.Schedule(handle);
                    // var newHandle = job.Schedule();
                    // handle = JobHandle.CombineDependencies(handle, newHandle);
                    Debug.Log($"<color=blue>job {iFixed} scheduled on frame {Time.frameCount}</color>");
                    asyncJobSystem.CompleteAsync(handle, promises[iFixed]);
                };
            }

            queueData.AddActionsAsync(actions)
            .Then(() =>
            {
                Debug.Log($"all jobs scheduled on frame {Time.frameCount}");
                Promise.All(promises)
                .Then(() =>
                {
                    Debug.Log($"handle complete status: {handle.IsCompleted}");
                    handle.Complete();
                    Debug.Log($"all done on frame {Time.frameCount}, the result is {counter.Count}");
                    counter.Dispose();
                });
            });
        }


    }
}
