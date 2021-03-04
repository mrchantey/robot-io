import Ev3.Systems
from Ev3.Systems import motorSystem
from Ev3.Systems import sensorSystem
from Messages.Systems import messageReceiveSystem
from Sockets.Systems import socketSystem
# import Ev
# IP_ADDRESS = "192.168.1.4"
IP_ADDRESS = None
REMOTE_IP_ADDRESS = None
if(Ev3.Systems.isDeployed == True):
    IP_ADDRESS = "192.168.1.9"
    REMOTE_IP_ADDRESS = "192.168.1.4"
    IP_ADDRESS = "192.168.1.9"
else:
    socketSystem.debug = True
    IP_ADDRESS = "192.168.1.4"
    REMOTE_IP_ADDRESS = IP_ADDRESS
SERVER_PORT = 5000
CLIENT_PORT = 5001
remote_endpoint = (REMOTE_IP_ADDRESS, SERVER_PORT)

if __name__ == "__main__":
    messageReceiveSystem.AddChannelListener(32, motorSystem.OnMessage)
    server_socket = socketSystem.CreateSocket(SERVER_PORT, IP_ADDRESS)
    client_socket = socketSystem.CreateSocket(CLIENT_PORT, IP_ADDRESS, False)
    socketSystem.Connect(client_socket, remote_endpoint)
    print("Ahoy.Ev3.main initialized")
    try:
        while(True):
            sensorSystem.SendSensorInfo(client_socket)
            socketSystem.Update()
    except KeyboardInterrupt:
        print("exiting Ahoy.Ev3.main")
        pass
