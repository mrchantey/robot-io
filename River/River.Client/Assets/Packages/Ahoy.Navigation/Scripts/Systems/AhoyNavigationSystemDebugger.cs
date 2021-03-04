using UnityEngine;
using Unity.Entities;
namespace Ahoy.Navigation
{

    public class AhoyNavigationSystemDebugger : MonoBehaviour
    {

        public bool debugNodeSpawnerSystem;
        public bool debugNodeUpdaterSystem;


        NodeGroupSpawner spawnerSystem;
        NodeGroupUpdater updaterSystem;
        private void Awake()
        {
            spawnerSystem = World.Active.GetOrCreateSystem<NodeGroupSpawner>();
            updaterSystem = World.Active.GetOrCreateSystem<NodeGroupUpdater>();
            spawnerSystem.debug = debugNodeSpawnerSystem;
            updaterSystem.debug = debugNodeUpdaterSystem;
        }

        private void OnValidate()
        {
            if (spawnerSystem != null)
                spawnerSystem.debug = debugNodeSpawnerSystem;
            if (updaterSystem != null)
                updaterSystem.debug = debugNodeUpdaterSystem;
        }

    }

}