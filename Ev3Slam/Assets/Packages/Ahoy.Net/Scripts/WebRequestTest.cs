using UnityEngine;
using UnityEngine.Networking;
using System.Collections;
using Unity.Entities;

namespace Ahoy.Net
{

    public class WebRequestTest : InvocableMono
    {

        public string url = "www.google.com";

        Requests requests;
        private void OnEnable()
        {
            requests = World.Active.GetOrCreateSystem<Requests>();
        }

        public override void Invoke()
        {
            requests.Get(url)
                        .Then(request => { Debug.Log($"request succeeded, text: {request.downloadHandler.text}"); })
                        .Catch(ex => { Debug.Log($"request failed, error: {ex.Message}"); });
        }



    }

}