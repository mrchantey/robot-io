using UnityEngine;
using Ahoy;
using Unity.Entities;

namespace Ahoy.Navigation
{

    public class PathFollower : MonoBehaviour
    {

        public SeekMethod seekMethod;
        public new Transform transform;
        public Transform target;
        [Range(0, 10)]
        public float distanceThreshold = 1;

        public NullUnityEvent onPathUpdated;
        public NullUnityEvent onPathImpossible;
        public NullUnityEvent onTargetReached;

        int waypointIndex;
        Vector3[] waypoints;

        protected void OnEnable()
        {
            var pathGenerator = World.Active.GetOrCreateSystem<PathGenerator>();
            pathGenerator.AddPathToGenerate(new PathGenerateInfo()
            {
                start = transform,
                finish = target,
                onPathGenerated = SetPath
            });
        }

        public void SetPath(PathInfo info)
        {
            if (!info.success)
            {
                waypoints = null;
                onPathImpossible.Invoke();
                return;
            }
            waypoints = info.waypoints;
            if (waypoints.Length == 1)
            {
                waypoints = null;
                onTargetReached.Invoke();
                // return;
            }
            else
            {
                waypointIndex = 1;//skip the waypoint im on
            }
            // Debug.Log($"waypoints created: {info.waypoints.ElementsToString()}");
            // waypointIndex = 0;
            onPathUpdated.Invoke();
        }

        void Update()
        {
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