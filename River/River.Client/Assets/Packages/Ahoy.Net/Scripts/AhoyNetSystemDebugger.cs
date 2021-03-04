using UnityEngine;
using Unity.Entities;
namespace Ahoy.Net
{

    public class AhoyNetSystemDebugger : MonoBehaviour
    {

        public bool debugSocketSystem;
        public bool debugMessageReceiveSystem;


        AhoySocketSystem socketSystem;
        MessageReceiveSystem messageReceiveSystem;
        private void Awake()
        {
            socketSystem = World.Active.GetOrCreateSystem<AhoySocketSystem>();
            messageReceiveSystem = World.Active.GetOrCreateSystem<MessageReceiveSystem>();
            socketSystem.debug = debugSocketSystem;
            messageReceiveSystem.debug = debugMessageReceiveSystem;
        }

        private void OnValidate()
        {
            if (socketSystem != null)
                socketSystem.debug = debugSocketSystem;
            if (messageReceiveSystem != null)
                messageReceiveSystem.debug = debugMessageReceiveSystem;
        }

    }

}