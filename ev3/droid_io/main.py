import time

from udpServer.UdpServer import UdpServer
from droidMessage.droidMessage import DroidMessage
import ev3Commands

if __name__ == '__main__':
    # myIp = '192.168.1.9'
    myIp = '192.168.1.9'
    clientIp = '192.168.1.4'
    myPort = 5000
    clientPort = 5001

    droidMessage = DroidMessage(myIp, myPort)

    ev3Commands.Decorate(droidMessage, True)

    server = UdpServer(myIp, myPort)
    server.onReceive = droidMessage.Receive

    server.ConnectClient(clientIp, clientPort)

    def onPoke():
        print('i got poked!')

    def onPrintString(message):
        print('string received: "{}"'.format(message))

    droidMessage.onSendBytes = server.SendBytes

    droidMessage.onPoke = onPoke
    droidMessage.onPrintString = onPrintString

    try:
        while(True):
            # print("bang")
            server.Update()
        # time.sleep(1)
    except KeyboardInterrupt:
        for handler in droidMessage.stopHandlers:
            handler()
        pass
