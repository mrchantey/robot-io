using UnityEngine;
using UnityEngine.XR;

namespace Ahoy.SteamVR
{

    public class XRManager : MonoBehaviour
    {

        public bool enableXR;
        public GameObject[] XRGameObjects;

        void Awake()
        {
            XRSettings.enabled = enableXR;
            foreach (var go in XRGameObjects)
            {
                go.SetActive(enableXR);
            }
        }
    }

}