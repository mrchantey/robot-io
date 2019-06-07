//algorithm from Sebastian Lague
using UnityEngine;
using Ahoy;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;

namespace Experiments.Navigation
{
    public class NodeGroupRenderer : MonoBehaviour
    {

        public GameObject nodeContainerPrefab;

        // public Transform start;
        // public Transform end;

        PathGenerator pathGenerator;
        NodeGroupSpawner nodeGroupSpawner;
        NodeGroupUpdater nodeGroupUpdater;
        Dictionary<Vector2Int, NodeContainer> nodeContainers;

        private void OnEnable()
        {
            pathGenerator = World.Active.GetOrCreateSystem<PathGenerator>();
            pathGenerator.onPathGenerated.AddListener(SetPath);

            nodeGroupSpawner = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
            nodeGroupSpawner.onSpawn.AddListener(CreateContainers);
            nodeGroupUpdater = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
            nodeGroupUpdater.onUpdate.AddListener(UpdateContainers);
        }

        // void OnGroupUpdate(NodeGroup group)
        // {
        //     if (nodeContainers == null || group.nodes.Count != nodeContainers.Count)
        //         CreateContainers(group);
        //     else
        //         UpdateContainers(group);
        // }

        void UpdateContainers(NodeGroup group)
        {
            group.nodes.ForEach(kvp =>
            {
                nodeContainers[kvp.Key].SetNode(kvp.Value);
            });
        }

        void CreateContainers(NodeGroup group)
        {
            if (nodeContainers != null)
                foreach (var kvp in nodeContainers)
                {
                    GameObject.Destroy(kvp.Value.transform.gameObject);
                }

            nodeContainers = group.nodes.Select(kvp =>
              {
                  var node = kvp.Value;
                  var go = GameObject.Instantiate(nodeContainerPrefab, Vector3.zero, Quaternion.identity, transform);
                  var nodeContainer = go.GetComponent<NodeContainer>();
                  nodeContainer.SetNode(node);
                  // return n;
                  return nodeContainer;
              }).ToDictionary(nc => nc.node.id);

        }


        public void SetPath(PathInfo info)
        {
            if (!info.success)
            {
                Debug.Log($"no possible path");
                nodeContainers.ForEach(kvp => kvp.Value.MarkDefault());
                return;
            }
            nodeContainers.ForEach(kvp =>
            {
                var nodeContainer = kvp.Value;
                var pos = nodeContainer.node.position;
                if (!info.waypoints.Any(wp => wp == pos))
                    nodeContainer.MarkDefault();
                else if (info.waypoints[0] == pos)
                    nodeContainer.MarkStart();
                else if (info.waypoints.Last() == pos)
                    nodeContainer.MarkEnd();
                else
                    nodeContainer.MarkWaypoint();
            });

        }



        // private void OnDrawGizmos()
        // {
        //     if (group == null)
        //         return;
        //     var nodes = group.nodes;
        //     if (nodes == null)
        //         return;
        //     nodes.ForEach(kvp =>
        //     {
        //         Vector3 position = kvp.Value.position;
        //         Color col = Color.white * (kvp.Value.weight / noiseAmp);
        //         col.a = 1;
        //         Gizmos.color = col;
        //         Gizmos.DrawCube(position, Vector3.one * 0.1f);
        //     });
        //     if (path == null)
        //         return;
        //     path.ForEach((n, i) =>
        //     {
        //         if (i == path.Count - 1)
        //             return;
        //         Gizmos.color = Color.cyan;
        //         Gizmos.DrawLine(n.position, path[i + 1].position);

        //     });

        // }
    }

}