using UnityEngine;
using Ahoy;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;
using Unity.Collections;

namespace Ahoy.Navigation
{

    public class NodeGroupSpawner : ComponentSystem
    {

        EntityManager manager;
        EntityQuery query;
        ComponentType[] groupType;
        public AhoyEvent<NodeGroup> onSpawn;
        public AhoyEvent<NodeGroup> onAfterSpawn;

        protected override void OnCreate()
        {
            manager = World.Active.EntityManager;
            groupType = new ComponentType[] { typeof(NodeGroup) };
            query = manager.CreateEntityQuery(groupType);
            onSpawn = new AhoyEvent<NodeGroup>();
            onAfterSpawn = new AhoyEvent<NodeGroup>();
        }

        public void SpawnGroup(int resolution, float nodeSize, float noiseFreq, float noiseAmp)
        {
            var entities = query.ToEntityArray(Allocator.TempJob);
            entities.ForEach(e => manager.DestroyEntity(e));
            entities.Dispose();

            var group = new NodeGroup(resolution, nodeSize, noiseFreq, noiseAmp);

            var entity = manager.CreateEntity(groupType);
            manager.SetSharedComponentData(entity, group);
            onSpawn.Invoke(group);
            onAfterSpawn.Invoke(group);
        }

        protected override void OnUpdate() { }

    }


}