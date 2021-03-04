using UnityEngine;
using UnityEditor;
using System.Linq;

namespace Ahoy
{
#if UNITY_EDITOR
    public static class AssetUtility
    {
        public static void RunMainThreadAction(System.Action action)
        {
            var go = new GameObject("temp");
            var eve = go.AddComponent<MainThreadEvent>();
            eve.action = action;
        }

        public static void ClearAssetFolder(string folderPath)
        {
            GetAssetPaths(folderPath)
              .ForEach(path => AssetDatabase.DeleteAsset(path));
        }

        public static string[] GetAssetPaths(string folderPath)
        {
            return AssetDatabase.FindAssets("", new[] { folderPath })
              .Select(guid => AssetDatabase.GUIDToAssetPath(guid))
              .ToArray();
        }

        public static T[] GetAssetsAtPath<T>(string folderPath) where T : UnityEngine.Object
        {
            return GetAssetPaths(folderPath)
                .Select(p => AssetDatabase.LoadAssetAtPath<T>(p))
                .ToArray();
        }


        public static void SaveMeshAsset(string folderPath, Mesh mesh)
        {
            string assetPath = folderPath + "/" + mesh.name + ".mesh";
            AssetDatabase.CreateAsset(mesh, assetPath);
        }

        public static void SavePrefabAsset(string folderPath, GameObject instance)
        {
            string assetPath = folderPath + "/" + instance.name + ".prefab";
            PrefabUtility.SaveAsPrefabAsset(instance, assetPath);
            GameObject.DestroyImmediate(instance);
        }


    }

#endif
}