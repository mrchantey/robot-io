using Unity.Entities;
using Unity.Mathematics;
using Unity.Collections;
using UnityEngine;
using System.Linq;
using System.Collections.Generic;

namespace Ahoy.Entities
{

    public class ActionQueueSystem : ComponentSystem
    {

        EntityManager manager;
        EntityQuery query;
        ComponentType[] actionQueueType;
        EntityArchetype actionQueueArchetype;
        // List<ActionD

        protected override void OnCreate()
        {
            manager = World.Active.EntityManager;
            actionQueueType = new ComponentType[] { typeof(ActionQueueData) };
            actionQueueArchetype = manager.CreateArchetype(actionQueueType);
            query = manager.CreateEntityQuery(actionQueueType);
        }

        public void CreateQueue(ActionQueueData data)
        {
            var entity = manager.CreateEntity(actionQueueArchetype);
            manager.SetSharedComponentData(entity, data);
        }

        protected override void OnUpdate()
        {
            var entities = query.ToEntityArray(Allocator.TempJob);

            var frame = Time.frameCount;
            // Debug.Log($"i found {entities.Length} entities");
            entities.ForEach(e =>
            {
                var data = manager.GetSharedComponentData<ActionQueueData>(e);
                if ((frame + data.frameOffset) % data.frameModulo != 0 || data.items.Count == 0)
                    return;
                if (data.debug)
                    Debug.Log($"dispatching {data.name} on frame {frame}");
                Dispatch(data);
            });
            entities.Dispose();
        }

        void Dispatch(ActionQueueData data)
        {
            int updateCount = data.items.Count < data.maxDispatchesPerUpdate ? data.items.Count : data.maxDispatchesPerUpdate;
            for (int i = 0; i < updateCount; i++)
            {
                // Debug.Log($"{i}");
                if (data.debugFull)
                    Debug.Log($"dispatching {data.name} {data.items[i].id} added:{data.items[i].queueFrame} dispatched:{Time.frameCount}");
                data.items[i].action();
            }
            data.items.RemoveRange(0, updateCount);
        }

        protected override void OnDestroy()
        {

        }
    }
}