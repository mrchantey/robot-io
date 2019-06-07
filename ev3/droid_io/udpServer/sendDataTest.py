from udpServer.UdpServer import UdpServer

from droidMessage import utility
from droidMessage.droidMessage import DroidMessage

if __name__ == '__main__':
    serverIpAddress = "127.0.0.1"
    serverPort = 5000
    clientIpAddress = "123.32.255.2"
    clientPort = 4932
    server = DroidMessage(serverIpAddress, serverPort)
    client = DroidMessage(clientIpAddress, clientPort)

    def clientSendBytesCallback(msg):
        server.Receive(msg)

    def serverSendBytesCallback(msg):
        client.Receive(msg)

    def onPokeReply(ip, port):
        print('the poke responded: {}:{}'.format(ip, port))

    def onPoke():
        print('i got poked!')

    def onPrintString(message):
        print('string received: "{}"'.format(message))

    def onSetLRMotors(left, right):
        print("bang")

    server.onSetLRMotors = onSetLRMotors

    server.onSendBytes = serverSendBytesCallback
    client.onSendBytes = clientSendBytesCallback

    server.onPoke = onPoke
    server.onPrintString = onPrintString

    client.onPokeReply = onPokeReply
    client.SendPoke()
    client.SendPrintString("hello world")
    client.SendSetLRMotors(1, -0.9999999999)

# server.Receive(bMsg)

# print(utility.IntToBytes(390328))
# val = SendPingTest(ipAddress, port)
# print(val)
# ipBytes = IpToBytes(ipAddress)
# print(ipBytes)

# SendPrintMessage("hello world")
# server = UdpServer(5001)
# server.SendMessage("hello world", "127.0.0.1", 5000)
# for i in range(10):
# try:
#     while(True):
#         server.Update()
# except KeyboardInterrupt:
#     pass
