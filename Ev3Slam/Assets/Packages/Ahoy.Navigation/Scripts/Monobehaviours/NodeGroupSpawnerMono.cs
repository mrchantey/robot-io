using UnityEngine;
using Ahoy;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;
using Unity.Collections;

namespace Experiments.Navigation
{

    // [CreateAssetMenu(fileName = "NodeGroupSpawner", menuName = "Experiments.Navigation/NodeGroupSpawner", order = 0)]
    public class NodeGroupSpawnerMono : InvocableMono
    {
        [Range(0, 100)]
        public int resolution = 32;
        [Range(0.01f, 10)]
        public float nodeSize = 1;
        [Range(0, 1)]
        public float noiseFreq = 0.2f;
        [Range(0, 1000)]
        public float noiseAmp = 100;

        EntityManager manager;

        EntityQuery query;
        ComponentType[] groupType;
        NodeGroupSpawner nodeGroupSpawner;

        private void OnEnable()
        {
            nodeGroupSpawner = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
        }
        public override void Invoke()
        {
            nodeGroupSpawner.SpawnGroup(resolution, nodeSize, noiseFreq, noiseAmp);
        }


        private void OnDrawGizmos()
        {
            Vector3 boundsSize = Vector3.one * resolution * nodeSize;
            boundsSize.y = 0.1f;
            Gizmos.color = Color.white;
            Gizmos.DrawWireCube(transform.position, boundsSize);
        }

    }


}