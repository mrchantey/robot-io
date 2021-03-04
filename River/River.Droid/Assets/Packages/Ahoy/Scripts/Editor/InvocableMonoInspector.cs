using UnityEngine;
using UnityEditor;

namespace Ahoy
{


    [CustomEditor(typeof(InvocableMono), true)]
    public class InvocableMonoInspector : Editor
    {

        public override void OnInspectorGUI()
        {
            base.OnInspectorGUI();

            var invocable = (InvocableMono)target;

            if (GUILayout.Button("Invoke"))
                invocable.Invoke();
        }

    }
}