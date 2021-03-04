using UnityEngine;
using Unity.Entities;
using Unity.Collections;
using Unity.Jobs;

using System;
using System.Collections.Generic;

namespace Ahoy.Entities
{

    public class TestAsyncJobSystem : InvocableMono
    {

        public int numJobs = 1;
        [Range(1, 8)]
        public int iterations = 7;

        EntityManager manager;
        AsyncJobSystem system;

        protected override void Start()
        {
            Init();
        }

        void Init()
        {
            manager = World.Active.EntityManager;
            system = World.Active.GetOrCreateSystem<AsyncJobSystem>();
        }

        public override void Invoke()
        {
            TestAsyncJob();
        }

        struct Job : IJob
        {
            public int iterations;
            // public NativeCounter counter;
            public void Execute()
            {
                // counter.Increment();
                long iter = 10;
                for (int i = 0; i < iterations; i++) { iter *= 10; }
                Debug.Log($"iterating {iter} times");
                float a = 0;
                for (int i = 0; i < iter; i++)
                {
                    a += Mathf.Sqrt(32230);
                }
                // counter.Count += (int)a;
            }
        };


        void TestAsyncJob()
        {
            for (int i = 0; i < numJobs; i++)
            {
                int ii = i;
                var job = new Job()
                {
                    iterations = iterations
                };
                Debug.Log($"job scheduled on frame {Time.frameCount}");
                var handle = job.Schedule();
                system.CompleteAsync(handle)
                .Then(() =>
                {
                    Debug.Log($"job {ii} completed on frame {Time.frameCount}");
                });
            }
        }


    }
}
