// using UnityEngine;
// using Ahoy;
// using Ahoy.Net;
// using Unity.Entities;

// namespace River.Client
// {

//     public class Ev3Restful : MonoBehaviour
//     {

//         public string ipAddress = "127.0.0.1";
//         public int port = 5000;
//         public Requests requests;

//         [Range(-100, 100)]
//         public float spinSpeed = 50;
//         [Range(-100, 100)]
//         public float moveSpeed = 50;

//         bool isSending;
//         float sendTimeStamp;

//         private void OnEnable()
//         {
//             requests = World.Active.GetOrCreateSystem<Requests>();
//         }


//         public void Spin(float scalar)
//         {
//             float speed = scalar * spinSpeed;
//             SendCommand("setmotor", "port", "a", "speed", speed.ToString());
//         }

//         public void StopMoving()
//         {
//             SendCommand("setmotor", "port", "b", "speed", "0");
//             SendCommand("setmotor", "port", "c", "speed", "0");
//         }

//         public void MoveStraight(float scalar)
//         {
//             float speed = moveSpeed * scalar;
//             SendCommand("setmotor", "port", "b", "speed", speed.ToString());
//             SendCommand("setmotor", "port", "c", "speed", speed.ToString());
//         }

//         //turn right will have a scalar of -1
//         public void Turn(float scalar)
//         {
//             float speed = moveSpeed * scalar;
//             SendCommand("setmotor", "port", "b", "speed", speed.ToString());
//             SendCommand("setmotor", "port", "c", "speed", (-speed).ToString());
//         }

//         public void MoveLeft(float scalar)
//         {
//             float speed = moveSpeed * scalar;
//             SendCommand("setmotor", "port", "b", "speed", speed.ToString());
//             SendCommand("setmotor", "port", "c", "speed", (-speed).ToString());
//         }

//         public void MoveRight(float scalar)
//         {
//             float speed = moveSpeed * scalar;
//             SendCommand("setmotor", "port", "b", "speed", (-speed).ToString());
//             SendCommand("setmotor", "port", "c", "speed", speed.ToString());
//         }

//         public void Move(float leftSpeed, float rightSpeed)
//         {
//             SendCommand("setmotor", "port", "b", "speed", leftSpeed.ToString());
//             SendCommand("setmotor", "port", "c", "speed", rightSpeed.ToString());
//         }

//         void SendCommand(string command, string arg1K, string arg1V, string arg2K, string arg2V)
//         {
//             string url = $"http://{ipAddress}:{port}/command:{command},{arg1K}:{arg1V},{arg2K}:{arg2V}";
//             Send(url);
//         }
//         void SendCommand(string command, string arg1K, string arg1V)
//         {
//             string url = $"http://{ipAddress}:{port}/command:{command},{arg1K}:{arg1V}";
//             Send(url);
//         }
//         void SendCommand(string command)
//         {
//             string url = $"http://{ipAddress}:{port}/command:{command},";
//             Send(url);
//         }

//         void Send(string url)
//         {

//             if (isSending)
//             {
//                 Debug.Log($"requests busy..");
//                 return;
//             }
//             Debug.Log($"making request: {url}");
//             isSending = true;
//             sendTimeStamp = Time.time;
//             requests.Get(url)
//             .Then(req =>
//             {
//                 isSending = false;
//                 var dt = Time.time - sendTimeStamp;
//                 Debug.Log($"response received in {dt.ToString("0.00")} seconds:\n {req.downloadHandler.text}");
//             })
//             .Catch(ex =>
//             {
//                 isSending = false;
//                 Debug.Log($"error: {ex.Message}");
//             });
//         }

//     }

// }