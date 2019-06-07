from droidMessage import utility
from droidMessage import poke
from droidMessage import printString
from droidMessage import motors


class DroidMessage():

    def __init__(self, myIpAddress, myPort, channel=69):
        self.channel = channel
        self.ipAddressBytes = utility.IpToBytes(myIpAddress)
        self.portBytes = utility.IntToBytes(myPort)
        self.addressBytes = \
            self.ipAddressBytes\
            .__add__(self.portBytes)

        self.receiveHandlers = []
        self.stopHandlers = []
        poke.Decorate(self)
        printString.Decorate(self)
        motors.Decorate(self)

    def onSendBytes(self, msg):
        print("send callback not assigned")

    def Receive(self, bMsg):
        header = bMsg[:2]
        body = bMsg[2:]
        for handler in self.receiveHandlers:
            if(handler(header, body)):
                return True
        return False
