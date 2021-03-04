using UnityEngine;
using UnityEngine.UI;
namespace Ahoy
{

    [ExecuteInEditMode]
    public class OverlayText : MonoBehaviour
    {




        public Text text;
        public new GameObject gameObject;

        void Update()
        {
            if (gameObject != null)
                UpdateTextPosition();
        }

        void UpdateTextPosition()
        {
            var canvasSize = text.canvas.GetComponent<RectTransform>().sizeDelta;
            Vector3 viewPortPos = Camera.main.WorldToViewportPoint(gameObject.transform.position);
            Vector2 screenPos = viewPortPos * canvasSize;
            text.rectTransform.anchoredPosition = screenPos;
            text.gameObject.SetActive(viewPortPos.z > 0);
        }

    }
}