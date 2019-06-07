


using UnityEngine;

namespace Ahoy
{

    public class AssetEventListener<AssetEventT, UnityEventT, ValueT> : MonoBehaviour
    where AssetEventT : AssetEvent<ValueT, UnityEventT>
    where UnityEventT : UnityEngine.Events.UnityEvent<ValueT>
    {

        public AssetEventT assetEvent;
        public UnityEventT response;

        private void OnEnable()
        {
            assetEvent.AddListener(response);
        }
        private void OnDisable()
        {
            assetEvent.RemoveListener(response);
        }

        // public void Invoke(int val)
        // {
        //     response.Invoke(val);
        // }

    }
    // public class AssetEventListener< : MonoBehaviour
    // {

    // }

}