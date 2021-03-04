using UnityEngine;
using Unity.Entities;
using System;
using System.Collections.Generic;

namespace Ahoy.Navigation
{
    using NodeDict = Dictionary<Vector2Int, Node>;
    public struct NodeGroup : ISharedComponentData, IEquatable<NodeGroup>
    {
        static int uuidIncr;
        public int uuid;

        public NodeDict nodes { get; private set; }
        Bounds bounds;
        int resolution;
        float nodeSize;

        public NodeGroup(int _resolution, float _nodeSize, float noiseFreq = 0.1f, float noiseAmp = 1f)
        {
            nodeSize = _nodeSize;
            resolution = _resolution;
            nodes = new NodeDict(resolution * resolution);
            bounds = new Bounds(Vector3.zero, new Vector3(1, 0, 1) * nodeSize * resolution);
            for (int ix = 0; ix < resolution; ix++)
            {
                for (int iy = 0; iy < resolution; iy++)
                {
                    var position = bounds.min + new Vector3(
                        ix * nodeSize,
                        0,
                        iy * nodeSize);
                    var weight = Mathf.PerlinNoise(bounds.max.x + position.x * noiseFreq, bounds.max.z + position.z * noiseFreq) * noiseAmp;
                    // position.y = weight / noiseAmp;
                    var node = new Node()
                    {
                        id = new Vector2Int(ix, iy),
                        position = position,
                        width = nodeSize,
                        weight = weight,
                        normalWeight = weight / noiseAmp
                    };
                    nodes[node.id] = node;
                }
            }
            uuid = ++uuidIncr;
        }
        public List<Node> GetNeighbours(Node node)
        {
            List<Node> neighbours = new List<Node>();

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0)
                        continue;
                    Vector2Int i = node.id + new Vector2Int(x, y);
                    if (i.x >= 0 && i.x < resolution && i.y >= 0 && i.y < resolution)
                        neighbours.Add(nodes[i]);
                }
            }
            return neighbours;
        }

        public bool PositionToNode(Vector3 position, out Node node)
        {
            position = position.Add(nodeSize / 2);
            Vector3 absPosition = position + bounds.extents;
            var index = Vector3Int.FloorToInt(absPosition / nodeSize);
            return nodes.TryGetValue(new Vector2Int(index.x, index.z), out node);
        }
        public Vector2Int PositionToIndex(Vector3 position)
        {
            position = position.Add(nodeSize / 2);
            Vector3 absPosition = position + bounds.extents;
            var index = Vector3Int.FloorToInt(absPosition / nodeSize);
            return new Vector2Int(index.x, index.z);
        }


        public Node PositionToNearestNode(Vector3 position)
        {
            position = position.Add(nodeSize / 2);
            Vector3 absPosition = position + bounds.extents;
            var index = Vector3Int.FloorToInt(absPosition / nodeSize);
            index.Clamp(Vector3Int.zero, Vector3Int.one * (resolution - 1));
            // index.Clamp(Vector3Int.zero, Vector3Int.one * (resolution));
            return nodes[new Vector2Int(index.x, index.z)];
        }

        public bool Equals(NodeGroup other)
        {
            return uuid == other.uuid;
        }

        public override int GetHashCode()
        {
            return uuid;
        }

    }

}
// public List<Node> GetNeighbours(Node node)
// {
//     int maxI = resolution - 1;
//     int xMin = (int)Mathf.Max(node.id.x - 1, 0);
//     int xMax = (int)Mathf.Min(node.id.x + 1, maxI);
//     int yMin = (int)Mathf.Max(node.id.y - 1, 0);
//     int yMax = (int)Mathf.Min(node.id.y + 1, maxI);
//     var neighbours = new List<Node>(9);
//     for (int ix = xMin; ix <= xMax; ix++)
//     {
//         for (int iy = yMin; iy <= yMax; iy++)
//         {
//             neighbours.Add(nodes[new Vector2Int(ix, iy)]);
//         }
//     }
//     return neighbours;
// }