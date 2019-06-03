using UnityEngine;
using Ahoy;
using Ahoy.Net;
using Unity.Entities;

namespace Ev3Remote
{

    public class Remote : MonoBehaviour
    {

        public string ipAddress = "127.0.0.1";
        public int port = 5000;
        public Requests requests;

        [Range(-255, 255)]
        public float spinSpeed = 1;
        [Range(-255, 255)]
        public float moveSpeed = 1;

        private void OnEnable()
        {
            requests = World.Active.GetOrCreateSystem<Requests>();
        }


        public void Spin(float scalar)
        {
            float speed = scalar * spinSpeed;
            SendCommand("setmotor", "port", "a", "speed", speed.ToString());
        }

        public void StopMoving()
        {
            SendCommand("setmotor", "port", "b", "speed", "0");
            SendCommand("setmotor", "port", "c", "speed", "0");
        }

        public void MoveStraight(float scalar)
        {
            float speed = moveSpeed * scalar;
            SendCommand("setmotor", "port", "b", "speed", speed.ToString());
            SendCommand("setmotor", "port", "c", "speed", speed.ToString());
        }

        public void MoveLeft(float scalar)
        {
            float speed = moveSpeed * scalar;
            SendCommand("setmotor", "port", "b", "speed", speed.ToString());
            SendCommand("setmotor", "port", "c", "speed", (-speed).ToString());
        }

        public void MoveRight(float scalar)
        {
            float speed = moveSpeed * scalar;
            SendCommand("setmotor", "port", "b", "speed", (-speed).ToString());
            SendCommand("setmotor", "port", "c", "speed", speed.ToString());
        }

        public void Move(float leftSpeed, float rightSpeed)
        {
            SendCommand("setmotor", "port", "b", "speed", leftSpeed.ToString());
            SendCommand("setmotor", "port", "c", "speed", rightSpeed.ToString());
        }

        void SendCommand(string command, string arg1K, string arg1V, string arg2K, string arg2V)
        {
            string url = $"http://{ipAddress}:{port}/command:{command},{arg1K}:{arg1V},{arg2K}:{arg2V}";
            Send(url);
        }
        void SendCommand(string command, string arg1K, string arg1V)
        {
            string url = $"http://{ipAddress}:{port}/command:{command},{arg1K}:{arg1V}";
            Send(url);
        }
        void SendCommand(string command)
        {
            string url = $"http://{ipAddress}:{port}/command:{command},";
            Send(url);
        }

        void Send(string url)
        {

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