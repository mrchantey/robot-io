using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.ARFoundation;
using System.Linq;
using Ahoy.Net;
using Ahoy;

public class PointCloudUpdateEvent : MonoBehaviour
{

    public ARPointCloudManager pointCloudManager;
    // [Space]
    [Header("message name: 'pointCloudIdentifiers'")]
    public bool updateIdentifiers;
    public IntArrayUnityEvent onIdentifiersUpdated;
    [Header("message name: 'pointCloudPositions'")]
    public bool updatePositions;
    public Vector3ArrayUnityEvent onPositionsUpdated;

    void Start()
    {
        pointCloudManager.pointCloudsChanged += OnPointCloudsChanged;
    }


    void OnPointCloudsChanged(ARPointCloudChangedEventArgs args)
    {
        args.updated.ForEach(OnPointCloudUpdated);
    }

    void OnPointCloudUpdated(ARPointCloud cloud)
    {
        if (cloud.positions.Length == 0)
            return;
        if (updateIdentifiers)
            onIdentifiersUpdated.Invoke(cloud.identifiers.Select(i => (int)i).ToArray());
        if (updatePositions)
            onPositionsUpdated.Invoke(cloud.positions.ToArray());
    }
}
