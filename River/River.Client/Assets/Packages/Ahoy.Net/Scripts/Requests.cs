using Unity.Entities;
using Unity.Mathematics;
using Unity.Transforms;
using UnityEngine;
// using Unity.Networking;
using UnityEngine.Networking;
using Ahoy;
using System.Collections.Generic;
using System.Linq;

namespace Ahoy.Net
{

    public class Requests : ComponentSystem
    {

        public List<RequestInfo> requests;

        protected override void OnCreate()
        {
            requests = new List<RequestInfo>();
        }

        public Promise<UnityWebRequest> Get(string url)
        {
            var request = UnityWebRequest.Get(url);
            var info = AddRequest(request);
            return info.promise;
        }

        protected override void OnUpdate()
        {
            requests
            .Where(ri => ri.operation.isDone)
            .ForEach(HandleDone);
            requests.RemoveAll(ri => ri.operation.isDone);
        }

        RequestInfo AddRequest(UnityWebRequest request)
        {
            var promise = new Promise<UnityWebRequest>();
            // request.uploadHandler.contentType = "Application/json";
            var operation = request.SendWebRequest();
            var requestInfo = new RequestInfo()
            {
                operation = operation,
                request = request,
                promise = promise
            };
            requests.Add(requestInfo);
            return requestInfo;
        }

        void HandleDone(RequestInfo info)
        {
            if (info.request.isNetworkError || info.request.isHttpError)
            {
                // Debug.Log(info.request.error);
                info.promise.Reject(new System.Exception(info.request.error));
            }
            else
            {
                info.promise.Resolve(info.request);
            }
        }



    }
    public struct RequestInfo
    {
        public AsyncOperation operation;
        public UnityWebRequest request;
        public Promise<UnityWebRequest> promise;
    }
}

// }