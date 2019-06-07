using UnityEngine;
using System;

namespace Experiments.Navigation
{

    [System.Serializable]
    public class Node : IHeapItem<Node>
    {
        public Vector2Int id;
        public bool isTraversable = true;
        public Vector3 position;
        public float width;
        public float weight;
        public float normalWeight;
        public Node parent;
        public float pathCost = float.MaxValue;
        public float endCost = float.MaxValue;
        public float cost { get { return pathCost + endCost + weight; } }
        // float fcost { get { return pathCost + endCost; } }


        public static float Distance(Node a, Node b)
        {
            int dstX = Mathf.Abs(a.id.x - b.id.x);
            int dstY = Mathf.Abs(a.id.y - b.id.y);
            if (dstX > dstY)
                return 1.4f * dstY + (dstX - dstY);
            else
                return 1.4f * dstX + (dstY - dstX);
        }


        public int HeapIndex
        {
            get; set;
        }
        public int CompareTo(Node nodeToCompare)
        {
            int compare = cost.CompareTo(nodeToCompare.cost);
            if (compare == 0)
            {
                compare = endCost.CompareTo(nodeToCompare.endCost);
            }
            return -compare;
        }

    }
}