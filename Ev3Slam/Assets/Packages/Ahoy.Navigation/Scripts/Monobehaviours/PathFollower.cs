using UnityEngine;
using Ahoy;
using Unity.Entities;

namespace Experiments.Navigation
{

    public class PathFollower : InvocableMono
    {


        public Transform target;
        [Range(0, 10)]
        public float speed = 1;
        [Range(0, 10)]
        public float distanceThreshold = 1;

        PathGenerator pathGenerator;
        NodeGroupSpawner nodeGroupSpawner;
        NodeGroupUpdater nodeGroupUpdater;
        int waypointIndex;
        Vector3[] waypoints;


        private void OnEnable()
        {
            pathGenerator = World.Active.GetOrCreateSystem<PathGenerator>();
            nodeGroupSpawner = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
            nodeGroupSpawner.onSpawn.AddListener(_ => Invoke());
            nodeGroupUpdater = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
            nodeGroupUpdater.onUpdate.AddListener(_ => Invoke());
        }

        public override void Invoke()
        {
            var info = pathGenerator.GeneratePath(transform.position, target.position);
            if (!info.success)
                return;
            waypointIndex = 1;//skip the point im on
            // waypointIndex = 0;
            waypoints = info.waypoints;

            // var path = nodeGridGenerator.group
        }
        protected override void Update()
        {
            base.Update();
            FollowPath();
        }

        public void FollowPath()
        {
            if (waypoints == null)
                return;
            var dist = Vector3.Distance(transform.position, waypoints[waypointIndex]);
            if (dist < distanceThreshold)
            {
                waypointIndex++;
                if (waypointIndex >= waypoints.Length)
                {
                    waypoints = null;
                    return;
                }
            }

            transform.LookAt(waypoints[waypointIndex]);
            Vector3 translation = Vector3.forward * speed * Time.deltaTime;
            transform.Translate(translation, Space.Self);
        }

        private void OnDrawGizmosSelected()
        {
            if (waypoints == null)
                return;
            waypoints.ForEach(wp =>
            {
                Gizmos.color = Color.yellow;
                Gizmos.DrawWireSphere(wp, distanceThreshold);
            });

        }


    }

}