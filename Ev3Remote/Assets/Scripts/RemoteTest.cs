using UnityEngine;
using Ahoy;
using Ahoy.Net;
using Unity.Entities;

namespace Ev3Remote
{

    public class RemoteTest : InvocableMono
    {

        public string ipAddress = "127.0.0.1";
        public int port = 5000;
        public Requests requests;

        private void OnEnable()
        {
            requests = World.Active.GetOrCreateSystem<Requests>();
        }


        public override void Invoke()
        {
            string url = $"http://{ipAddress}:{port}/command/sayhello";
            Debug.Log($"making request: {url}");
            requests.Get(url)
            .Then(req =>
            {
                Debug.Log($"response received {req.downloadHandler.text}");
            })
            .Catch(ex =>
            {
                Debug.Log($"error: {ex.Message}");
            });

        }

    }

}