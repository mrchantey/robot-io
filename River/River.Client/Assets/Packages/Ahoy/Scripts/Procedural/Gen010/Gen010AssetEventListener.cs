using UnityEngine;
using UnityEngine.Events;
using System.Collections.Generic;
using System;
using System.Linq;

namespace Ahoy
{
    public class Gen010AssetEventListener : MonoBehaviour
    {

        public Gen010AssetEvent assetEvent;
        public Gen010UnityEvent response;


        private void OnEnable()
        {
            assetEvent.AddListener(response);
        }
        private void OnDisable()
        {
            assetEvent.RemoveListener(response);
        }
    }
}