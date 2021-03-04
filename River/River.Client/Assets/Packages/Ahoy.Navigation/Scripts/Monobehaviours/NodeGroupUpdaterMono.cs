using UnityEngine;
using Ahoy;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;
using Unity.Collections;

namespace Ahoy.Navigation
{

    // [CreateAssetMenu(fileName = "NodeGroupUpdater", menuName = "Ahoy.Navigation/NodeGroupUpdater", order = 0)]
    public class NodeGroupUpdaterMono : InvocableMono
    {
        public bool clearValidNodes = true;
        public bool updateCollisions = true;

        [Range(-10, 10)]
        public float heightMin = -1;
        [Range(-10, 10)]
        public float heightMax = 1;
        [Header("Random Sphere test settings")]
        public bool updateFromRandomSphere = true;
        [Range(0, 1000)]
        public int testNumPoints = 50;
        [Range(0, 100)]
        public float testRadius = 10;
        // public bool updateCollisions = true;


        EntityManager manager;

        EntityQuery query;
        ComponentType[] groupType;
        NodeGroupUpdater nodeGroupUpdater;

        List<Vector3> debugPoints;

        protected void OnEnable()
        {
            debugPoints = new List<Vector3>();
            nodeGroupUpdater = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
        }

        public void UpdateCollisions()
        {
            nodeGroupUpdater.UpdateFromCollisions(clearValidNodes);

        }

        public void UpdateFromPoints(Vector3[] points)
        {
            nodeGroupUpdater.UpdateFromPoints(points, heightMin, heightMax, clearValidNodes);
            if (clearValidNodes)
                debugPoints = points.ToList();
            else
                debugPoints.AddRange(points);
        }

        public override void Invoke()
        {
            if (updateCollisions)
                UpdateCollisions();
            if (updateFromRandomSphere)
            {
                var points = new Vector3[testNumPoints];
                for (int i = 0; i < testNumPoints; i++)
                {
                    // points[i] = Random.onUnitSphere * testRadius;
                    points[i] = Random.insideUnitSphere * testRadius;
                }
                UpdateFromPoints(points);
            }

        }

        private void OnDrawGizmosSelected()
        {

            if (debugPoints != null)
            {
                debugPoints.ForEach(dp =>
                {
                    if (dp.y > heightMax || dp.y < heightMin)
                        Gizmos.color = new Color(Color.red.r, Color.red.g, Color.red.b, 0.1f);
                    else
                        Gizmos.color = Color.green;
                    Gizmos.DrawWireSphere(dp, 0.1f);
                });
            }

        }


    }
}