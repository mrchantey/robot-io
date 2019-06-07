import time

from udpServer.UdpServer import UdpServer
from droidMessage.droidMessage import DroidMessage

if __name__ == '__main__':
    myIp = '192.168.1.4'
    serverIp = '192.168.1.9'
    myPort = 5001
    serverPort = 5000
    droidMessage = DroidMessage(myIp, myPort)
    server = UdpServer(myIp, myPort)
    server.onReceive = droidMessage.Receive

    droidMessage.onSendBytes = server.SendBytes

    server.ConnectClient(serverIp, serverPort)

    def onPokeReply(ip, port):
        print('they responded to a poke {}:{}'.format(ip, port))

    droidMessage.onPokeReply = onPokeReply
    # droidMessage.SendPoke()
    # droidMessage.SendPrintString("hello world")
    # droidMessage.SendPrintString("wake up jeff! {}".format(time.time))
    # droidMessage.SendSetLRMotors(1, -0.9999999999)
    count = 0
    try:
        # while(True):
        # time.sleep(1)
        while (True):
            val = float(input("speed: "))
            print("setting speed to {}".format(val))
            droidMessage.SendSetAux1Motor(val)

        # for i in range(100):
        # droidMessage.SendSetLRMotors(0, 0)
        # droidMessage.SendPrintString("wake up jeff! {}".format(count))
        # count = count + 1
        # droidMessage.SendPrintString("wake up jeff! {}".format(time.time()))
        # droidMessage.SendSetLRMotors(1, -0.9999999999)
        # server.Update()
    except KeyboardInterrupt:
        pass
