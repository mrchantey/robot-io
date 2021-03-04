
from Sockets.Systems import socketSystem
from Messages.Message import Message
from Messages import MessageUtility

IP_ADDRESS = "192.168.1.4"
PORT = 5000

EV3_ENDPOINT = ("192.168.1.9", 5000)


if __name__ == "__main__":
    socket = socketSystem.CreateSocket(PORT, IP_ADDRESS)
    socketSystem.Connect(socket, EV3_ENDPOINT)
    msg = Message(32, 0, MessageUtility.DataType.Float, [0])
    barr = MessageUtility.MessageToBytes(msg)
    socketSystem.SendData(socket, barr)
