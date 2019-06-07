import random
import socket
import select
import json


class UdpServer():
    def __init__(self, ipAddress, port, bufferSize=1024, maxMessageLength=64):
        self.maxMessageLength = maxMessageLength
        self.bufferSize = bufferSize
        self.buffer = bytearray(bufferSize)
        self.onReceive = lambda msg: print("on receive callback")
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((ipAddress, port))
        # self.socket.setblocking(False)
        print("server initialized")

        self.client = None

    def Update(self):
        toread = self.bufferSize
        buffView = memoryview(self.buffer)
        buffIndex = 0
        while(toread):
            receiving = select.select([self.socket], [], [], 0)[0]
            if(len(receiving) == 0):
                return
            # if(buffIndex > self.bufferSize):
            if(buffIndex + self.maxMessageLength > self.bufferSize):
                print("maxed out")
                return
            (msgLen, sender) = self.socket.recvfrom_into(buffView, toread)
            buffView = buffView[msgLen:]
            print("iterating toread: {} nbytes: {} buffer index: {}".format(toread, msgLen, buffIndex))
            buffSlice = self.buffer[buffIndex:buffIndex+msgLen]
            # print(buffSlice)
            buffIndex += msgLen
            toread -= msgLen
            self.onReceive(buffSlice)

    def ConnectClient(self, ipAddress, port):
        self.client = (ipAddress, port)

    def SendBytes(self, bMsg):
        if(self.client == None):
            print("no clients connected")
        else:
            self.socket.sendto(bMsg, self.client)


# if __name__ == '__main__':
    # server = UdpServer(5000)
    # for i in range(10):
    # try:
    #     while(True):
    #         server.Update()
    # except KeyboardInterrupt:
    #     pass
