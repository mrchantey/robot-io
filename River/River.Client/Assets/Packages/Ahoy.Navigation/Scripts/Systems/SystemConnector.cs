using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;

namespace Ahoy.Navigation
{

    public class SystemConnector : ComponentSystem
    {

        EntityManager manager;

        protected override void OnCreate()
        {


            manager = World.Active.EntityManager;
            var nodeGroupSpawner = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
            var nodeGroupUpdater = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
            var pathGenerator = World.Active.GetOrCreateSystem<PathGenerator>();

            nodeGroupSpawner.onSpawn.AddListener(pathGenerator.SetNodeGroup);
            nodeGroupUpdater.onUpdate.AddListener(pathGenerator.GeneratePaths);


        }
        protected override void OnUpdate()
        {
        }
    }
}