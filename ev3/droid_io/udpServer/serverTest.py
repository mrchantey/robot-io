import time

from udpServer.UdpServer import UdpServer
from droidMessage.droidMessage import DroidMessage

if __name__ == '__main__':
    myIp = '192.168.1.4'
    myPort = 5000
    clientPort = 5001
    droidMessage = DroidMessage(myIp, myPort)
    server = UdpServer(myIp, myPort)
    server.onReceive = droidMessage.Receive

    server.ConnectClient(myIp, clientPort)

    def onPoke():
        print('i got poked!')

    def onPrintString(message):
        print('string received: "{}"'.format(message))

    def onSetLRMotors(left, right):
        print("bang")

    droidMessage.onSendBytes = server.SendBytes

    droidMessage.onPoke = onPoke
    droidMessage.onPrintString = onPrintString
    droidMessage.onSetLRMotors = onSetLRMotors

    try:
        while(True):
            # print("bang")
            server.Update()
        # time.sleep(1)
    except KeyboardInterrupt:
        pass
