using UnityEngine;

namespace Ahoy.Net
{

    [CreateAssetMenu(fileName = "IpInfo", menuName = "Ahoy.Net/IpInfo", order = 0)]
    public class IpInfo : ScriptableObject
    {
        public string deviceName;
        public string ipAddress;
        public string macAddress;
        public int port;
    }

}