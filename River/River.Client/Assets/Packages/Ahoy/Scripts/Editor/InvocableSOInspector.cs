using UnityEngine;
using UnityEditor;

namespace Ahoy
{


    [CustomEditor(typeof(InvocableSO), true)]
    public class InvocableSOInspector : Editor
    {


        public override void OnInspectorGUI()
        {
            base.OnInspectorGUI();

            var invocable = (InvocableSO)target;

            if (GUILayout.Button("Invoke"))
                invocable.Invoke();
        }

    }
}