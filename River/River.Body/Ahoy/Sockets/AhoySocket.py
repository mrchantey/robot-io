import socket
from Ahoy.AhoyList import AhoyList

# in python endpoints are simply tuples (ipaddress,port)


class AhoySocket():
    def __init__(self, port, ipAddress="127.0.0.1"):

        self.__socket__ = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # self.__socket__.setblocking(True)
        # self.__socket__.
        # self.localEndPoint = ("0.0.0.0", port)
        self.localEndPoint = (ipAddress, port)
        self.__socket__.bind(self.localEndPoint)
        # self.remoteEndPoints = AhoyList()
        # self.__socket__.recv

    def __str__(self):
        return self.localEndPoint[0] + ":" + str(self.localEndPoint[1])
