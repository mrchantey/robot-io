using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.ARFoundation;
using UnityEngine.UI;
using Ahoy;
using Ahoy.Net;


public class ARTest : MonoBehaviour
{
    public ARPointCloudManager pointCloudManager;
    public Text textLog;
    public Text textUpdate;
    string log = "";
    Dictionary<ulong, Vector3> points;


    public SerializableVector3ArrayUnityEvent onPointsUpdate;
    private void OnEnable()
    {
        points = new Dictionary<ulong, Vector3>();
        pointCloudManager.pointCloudsChanged += OnPointCloudsChanged;
    }

    void OnPointCloudsChanged(ARPointCloudChangedEventArgs args)
    {
        args.updated.ForEach(UpdatePoints);

        textUpdate.text = $"total points: {points.Count}";

        var str = $"\n{Time.time.ToString("0.0")} - clouds changed: \nadded: {args.added.Count}\nupdated: {args.updated.Count}\nremoved: {args.removed.Count}";
        log += str;
        textLog.text = log;
    }
    void UpdatePoints(ARPointCloud pointCloud)
    {
        var newPoints = new List<Vector3>();
        for (int i = 0; i < pointCloud.positions.Length; i++)
        {
            var id = pointCloud.identifiers[i];
            var val = pointCloud.positions[i];
            Vector3 val2;
            if (!points.TryGetValue(id, out val2))
                newPoints.Add(val);
            points[id] = val;
        }
        if (newPoints.Count > 0)
        {
            onPointsUpdate.Invoke(SerializableVector3.ToSerializableVector3(newPoints.ToArray()));
        }
    }

}
