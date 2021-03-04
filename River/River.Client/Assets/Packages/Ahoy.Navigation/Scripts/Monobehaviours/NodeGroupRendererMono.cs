//algorithm from Sebastian Lague
using UnityEngine;
using Ahoy;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;

namespace Ahoy.Navigation
{
    public class NodeGroupRendererMono : MonoBehaviour
    {

        public GameObject nodeContainerPrefab;

        // public Transform start;
        // public Transform end;

        // NodeGroupSpawner nodeGroupSpawner;
        // NodeGroupUpdater nodeGroupUpdater;
        public bool debug;
        Dictionary<Vector2Int, NodeContainer> nodeContainers;

        private void OnEnable()
        {
            var nodeGroupSpawner = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
            nodeGroupSpawner.onSpawn.AddListener(CreateContainers);
            var nodeGroupUpdater = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
            nodeGroupUpdater.onUpdate.AddListener(UpdateContainers);
            var pathGenerator = World.Active.GetOrCreateSystem<PathGenerator>();
            pathGenerator.onPathsGenerated.AddListener(UpdateContainers);
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

        void UpdateContainers()
        {
            if (debug)
                Debug.Log($"renderer - updating containers");
            nodeContainers.ForEach(kvp => kvp.Value.MarkDefault());
        }


        void UpdateContainers(PathInfo[] infos)
        {
            // Debug.Log($"renderer - updating containers with path");
            // Debug.Log($"infos: {infos.ElementsToString()}");
            var waypoints = infos
            .Where(i => i.waypoints != null)
            .SelectMany(i => i.waypoints)
            .ToArray();
            var starts = infos.SelectMany(i => new Vector3[] { i.waypoints[0] });
            var ends = infos.SelectMany(i => new Vector3[] { i.waypoints[i.waypoints.Length - 1] });
            nodeContainers.ForEach(kvp =>
            {
                var container = kvp.Value;
                var node = kvp.Value.node;
                var pos = kvp.Value.node.position;
                // container.SetNode(group.nodes[container.node.id]);
                if (!waypoints.Any(wp => wp == pos))
                    container.MarkDefault();
                else if (starts.Any(s => s == pos))
                    container.MarkStart();
                else if (ends.Any(e => e == pos))
                    container.MarkEnd();
                else
                    container.MarkWaypoint();
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