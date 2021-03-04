using UnityEngine;
using Ahoy;
using Unity.Entities;

namespace Ahoy.Navigation
{

    public class PathFollower : InvocableMono
    {

        public SeekMethod seekMethod;

        public Transform target;
        [Range(0, 10)]
        public float distanceThreshold = 1;

        PathGenerator pathGenerator;
        NodeGroupSpawner nodeGroupSpawner;
        NodeGroupUpdater nodeGroupUpdater;
        public PathInfoUnityEvent onPathGenerated;
        public NullUnityEvent onPathImpossible;
        public NullUnityEvent onTargetReached;

        int waypointIndex;
        Vector3[] waypoints;


        protected void OnEnable()
        {
            pathGenerator = World.Active.GetOrCreateSystem<PathGenerator>();
            nodeGroupSpawner = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
            nodeGroupSpawner.onAfterSpawn.AddListener(_ => Invoke());
            nodeGroupUpdater = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
            nodeGroupUpdater.onAfterUpdate.AddListener(_ => Invoke());
        }

        public override void Invoke()
        {
            var info = pathGenerator.GeneratePath(transform.position, target.position);
            if (!info.success)
            {
                onPathImpossible.Invoke();
                return;
            }
            waypointIndex = 1;//skip the waypoint im on
            // waypointIndex = 0;
            waypoints = info.waypoints;
            onPathGenerated.Invoke(info);
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
                    onTargetReached.Invoke();
                    return;
                }
            }
            var target = waypoints[waypointIndex];
            seekMethod.SeekTarget(transform, target);
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