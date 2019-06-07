using UnityEngine;
using UnityEditor;
using System.Collections.Generic;

namespace Ahoy

{
    [CreateAssetMenu(fileName = "PackageImporter", menuName = "Ahoy/PackageImporter", order = 0)]
    [ExecuteAlways]
    public class PackageImporter : InvocableSO
    {
        public bool selectContents;
        public string path = "../../unity-packages/Ahoy";
        public List<string> paths;
        

        public bool debug;
        bool debugCallbacksAdded;

        public override void Invoke()
        {
#if UNITY_EDITOR
            if (debug && !debugCallbacksAdded)
            {
                AssetDatabase.importPackageCompleted += OnAdded;
                AssetDatabase.importPackageCancelled += OnCancelled;
                AssetDatabase.importPackageFailed += OnFailed;
                debugCallbacksAdded = true;
            }
            else if (!debug && debugCallbacksAdded)
            {
                AssetDatabase.importPackageCompleted -= OnAdded;
                AssetDatabase.importPackageCancelled -= OnCancelled;
                AssetDatabase.importPackageFailed -= OnFailed;
                debugCallbacksAdded = false;
            }
            var packagePath1 = $"{path}.unitypackage";
            AssetDatabase.ImportPackage(packagePath1, selectContents);
            paths.ForEach(p =>
        {
            var packagePath = $"{p}.unitypackage";
            AssetDatabase.ImportPackage(packagePath, selectContents);
        });
#endif
        }


        void OnAdded(string val)
        {
            Debug.Log($"package import succedded:\n{val}`");
        }
        void OnCancelled(string val)
        {
            Debug.Log($"package import cancelled:\n{val}`");
        }
        void OnFailed(string valA, string valB)
        {
            Debug.Log($"package import failed:\n{valA}\n{valB}`");
        }

    }
}