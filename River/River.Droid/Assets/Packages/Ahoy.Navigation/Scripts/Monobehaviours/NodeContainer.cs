using UnityEngine;

namespace Ahoy.Navigation
{
    public class NodeContainer : MonoBehaviour
    {

        public Node node;
        Material material;
        public Color defaultColor = Color.cyan;
        public Color nonTraversableColor = Color.red;
        public Color startColor = Color.blue;
        public Color endColor = Color.green;
        public Color waypointColor = Color.yellow;

        private void OnEnable()
        {
            material = GetComponentInChildren<MeshRenderer>().material;
        }


        public void SetNode(Node _node)
        {
            node = _node;
            transform.position = node.position;
            transform.localScale = Vector3.one * node.width;
            MarkDefault();
        }
        public void MarkStart()
        {
            material.SetColor("_Color", startColor);
        }
        public void MarkEnd()
        {
            material.SetColor("_Color", endColor);
        }

        public void MarkWaypoint()
        {
            material.SetColor("_Color", waypointColor);
        }
        public void MarkDefault()
        {
            if (node.isTraversable)
            {
                var col = new Color(
                defaultColor.r * node.normalWeight,
                defaultColor.g * node.normalWeight,
                defaultColor.b * node.normalWeight);
                // defaultColor *= ;
                material.SetColor("_Color", col);
            }
            else
            {
                material.SetColor("_Color", nonTraversableColor);
            }
        }
    }
}