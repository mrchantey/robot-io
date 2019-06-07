using System;
using System.IO;
using System.Collections;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using Ahoy;
using UnityEngine;
namespace Ahoy.Net
{


    public class SerializeTest : InvocableMono
    {

        public override void Invoke()
        {
            // var myMsg = new StringMessage() { value = "hello, world" };
            var arrVector3 = new Vector3[] { Vector3.left, Vector3.up, Vector3.right, Vector3.down };
            var arr = SerializableVector3.ToSerializableVector3(arrVector3);
            var bytes = Messaging.ObjectToBytes(arr);
            var msg = Messaging.BytesToObject<SerializableVector3[]>(bytes);
            var deserializedArrSerializableVector3 = SerializableVector3.ToVector3(msg);
            Debug.Log($"deserialized: {deserializedArrSerializableVector3.ElementsToString()}");
        }
    }
}