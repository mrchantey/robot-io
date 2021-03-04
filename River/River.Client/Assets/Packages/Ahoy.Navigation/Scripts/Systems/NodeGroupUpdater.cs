using UnityEngine;
using Ahoy;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;
using Unity.Collections;

namespace Ahoy.Navigation
{

    public class NodeGroupUpdater : ComponentSystem
    {

        EntityManager manager;
        EntityQuery query;
        ComponentType[] groupType;
        public ConsumableAhoyEvent onUpdate;
        public bool debug;

        protected override void OnCreate()
        {
            manager = World.Active.EntityManager;
            groupType = new ComponentType[] { typeof(NodeGroup) };
            query = manager.CreateEntityQuery(groupType);
            onUpdate = new ConsumableAhoyEvent();
        }

        public void UpdateFromCollisions(bool clearValidNodes = true)
        {
            var entities = query.ToEntityArray(Allocator.TempJob);
            if (debug)
                Debug.Log($"node group updater - updating from collisions");
            entities.ForEach(e =>
            {
                var group = manager.GetSharedComponentData<NodeGroup>(e);
                group.nodes.Values.ForEach(node => TestForCollisions(node, clearValidNodes));
                onUpdate.Invoke();
            });
            entities.Dispose();
        }
        public void UpdateFromPoints(Vector3[] points, float heightMin, float heightMax, bool clearValidNodes = true)
        {
            var entities = query.ToEntityArray(Allocator.TempJob);
            // var indicies = 
            var validPoints = points.Where(p => p.y >= heightMin && p.y <= heightMax).ToArray();
            if (debug)
                Debug.Log($"node group updater - updating from points, valid point count: {validPoints.Length}, points: {validPoints.ElementsToString()}");
            entities.ForEach(e =>
            {
                var group = manager.GetSharedComponentData<NodeGroup>(e);
                group.nodes.Values.ForEach(node => TestForPointIntersect(node, group, validPoints, clearValidNodes));
                onUpdate.Invoke();
            });
            entities.Dispose();
        }

        void TestForPointIntersect(Node node, NodeGroup group, Vector3[] points, bool clearValidNodes)
        {
            if (points.Any(p => group.PositionToIndex(p) == node.id))
                node.isTraversable = false;
            else if (clearValidNodes)
                node.isTraversable = true;
        }

        void TestForCollisions(Node node, bool clearValidNodes)
        {
            var halfExtents = Vector3.one * (node.width * 0.5f);
            var colliders = Physics.OverlapBox(node.position, halfExtents);
            if (colliders.Any(c => c.GetComponent<Obstacle>() != null))
                node.isTraversable = false;
            else if (clearValidNodes)
                node.isTraversable = true;
        }
        protected override void OnUpdate() { }

    }


}