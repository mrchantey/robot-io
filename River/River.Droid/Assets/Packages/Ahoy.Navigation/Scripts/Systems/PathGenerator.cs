//algorithm from Sebastian Lague - pathfinding tutorial
// 03/06/19


using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;
using System.Collections.Generic;
using System.Linq;
using Unity.Collections;
using Ahoy;

namespace Ahoy.Navigation
{

    public class PathGenerator : ComponentSystem
    {

        EntityQuery groupQuery;
        EntityManager manager;

        public AhoyEvent<PathInfo> onPathGenerated;


        protected override void OnCreate()
        {
            manager = World.Active.EntityManager;
            onPathGenerated = new AhoyEvent<PathInfo>();
            groupQuery = manager.CreateEntityQuery(new ComponentType[] { typeof(NodeGroup) });
        }


        public PathInfo GeneratePath(Vector3 startPosition, Vector3 endPosition)
        {
            var info = new PathInfo();
            var entities = groupQuery.ToEntityArray(Allocator.TempJob);
            if (entities.Length == 0)
            {
                onPathGenerated.Invoke(info);
                return info;
            }
            var group = manager.GetSharedComponentData<NodeGroup>(entities[0]);
            // Debug.Log($"got the group with {group.nodes.Count} nodes");
            entities.Dispose();

            var openGroup = new Heap<Node>(group.nodes.Count);
            var closedGroup = new HashSet<Node>();

            Node startNode = group.PositionToNearestNode(startPosition);
            Node endNode = group.PositionToNearestNode(endPosition);

            startNode.pathCost = 0;
            startNode.endCost = Node.Distance(startNode, endNode);
            openGroup.Add(startNode);

            int count = 0;
            while (openGroup.Count > 0)
            {
                count++;
                Node current = openGroup.RemoveFirst();
                // Node current = GetOpenLowestCost();
                // openGroup.Remove(current);
                closedGroup.Add(current);
                if (current == endNode)
                {
                    // Debug.Log($"yay, found the path in {count} steps!");
                    info.success = true;
                    break;
                }

                var neighbours = group.GetNeighbours(current);
                neighbours.ForEach(next =>
                {
                    if (!next.isTraversable || closedGroup.Contains(next))
                        return;
                    float pathCost = current.pathCost + Node.Distance(current, next);
                    float endCost = Node.Distance(next, endNode);
                    float newCost = pathCost + endCost + next.weight;
                    if (newCost < next.cost || !openGroup.Contains(next))
                    {
                        next.pathCost = pathCost;
                        next.endCost = endCost;
                        next.parent = current;
                        if (!openGroup.Contains(next))
                            openGroup.Add(next);
                        else
                            openGroup.UpdateItem(next);
                    }

                });
            }
            if (info.success)
            {
                info.waypoints = GetWaypoints(startNode, endNode);
            }
            onPathGenerated.Invoke(info);
            return info;
        }

        Vector3[] GetWaypoints(Node startNode, Node endNode)
        {
            var path = new List<Node>();
            // Debug.Log(endNode.parent.id);
            // Debug.Log(startNode.parent.id);
            Node current = endNode;
            while (current != startNode)
            {
                path.Add(current);
                current = current.parent;
            }
            path.Add(startNode);
            path.Reverse();
            // waypoints.Reverse();
            var waypoints = path.Select(n => n.position).ToArray();
            waypoints = SimplifyWaypoints(waypoints);
            return waypoints;
            // var ids = path.Where(p => p.parent != null).Select(p => p.parent.id);
            // Debug.Log($"{ids.ElementsToString()}");
            // path.Select(p.p.parent)
        }

        Vector3[] SimplifyWaypoints(Vector3[] wpOld)
        {
            if (wpOld.Length < 2)
                return wpOld;
            var wpNew = new List<Vector3>();
            Vector3 lastDir = Vector3.zero;
            // wpNew.Add(wpOld.First());
            for (int i = 0; i < wpOld.Length - 1; i++)
            {
                Vector3 nextDir = Vector3.Normalize(wpOld[i + 1] - wpOld[i]);
                if (nextDir != lastDir)
                {
                    wpNew.Add(wpOld[i]);
                    lastDir = nextDir;
                }
            }
            wpNew.Add(wpOld.Last());
            return wpNew.ToArray();
        }

        protected override void OnUpdate()
        {
        }
    }
}

// Node GetOpenLowestCost()
// {
//     Node nMin = openGroup.First();
//     openGroup.ForEach(n => { if (n.cost < nMin.cost) nMin = n; });
//     return nMin;
// }

