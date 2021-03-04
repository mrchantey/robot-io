using UnityEngine;
using UnityEditor;
using System.Collections.Generic;

namespace Ahoy

{
    [CreateAssetMenu(fileName = "PackageExporter", menuName = "Ahoy/PackageExporter", order = 0)]
    public class PackageExporter : InvocableSO
    {
        public bool selectContents;
        public string assetPath = "Assets/Packages";
        public string fileName = "../../unity-packages/mypkg";

        public override void Invoke()
        {
#if UNITY_EDITOR
            AssetDatabase.ExportPackage(assetPath, $"{fileName}.unitypackage", ExportPackageOptions.Recurse);
#endif
        }

    }
}