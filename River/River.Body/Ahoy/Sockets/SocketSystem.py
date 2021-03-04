from Ahoy.AhoyEvent import AhoyEvent
from .AhoySocket import AhoySocket
from Sockets.SocketDataEventArgs import SocketDataEventArgs
from Ahoy.AhoyList import AhoyList
import select


class SocketSystem():
    def __init__(self, debug=False):
        self.debug = debug
        self.bufferSize = 10240  # 10 messages max
        self.maxMessageLength = 1024
        self.sockets = AhoyList()
        self.buffer = bytearray(self.bufferSize)
        self.onData = AhoyEvent()

    def CreateSocket(self, port, ipAddress="127.0.0.1", isServer=True):
        socket = AhoySocket(port, ipAddress)
        if(isServer):
            self.sockets.append(socket)
        if(self.debug):
            print("socket system - socket created: {}:{}".format(ipAddress, port))
        return socket

    def Connect(self, socket, endpoint):
        # socket.remoteEndPoints.TryAdd(endpoint)
        socket.__socket__.connect(endpoint)
        if(self.debug):
            print("socket system - endpoint connected: {}:{}".format(endpoint[0], endpoint[1]))

    def SendData(self, socket, data):
        socket.__socket__.sendall(data)
        if(self.debug):
            print("socket system - data send: \n\tfrom: {} \n\tdata: {}".format(socket, data))

    def Update(self):
        offset = 0
        buffView = memoryview(self.buffer)
        for socket in self.sockets:
            # segmentSize = self.bufferSize

            def IsReceiving():
                receiving = select.select([socket.__socket__], [], [], 0)[0]
                if(len(receiving) > 0):
                    return True
                else:
                    return False
            while(IsReceiving()):
                if(offset + self.maxMessageLength > self.bufferSize):
                    if(self.debug):
                        print("socket system - buffer overflow, please throttle messages or increase buffer size")
                    # print("offset")
                    return
                # if(self.debug):
                #     print("socket system - socket receiving: \n\tsocket: {}".format(socket))
                (received, sender) = socket.__socket__.recvfrom_into(buffView, self.maxMessageLength)
                # received = socket.__socket__.recv_ijklnto(buffView, self.maxMessageLength)
                # (received, sender) = socket.__socket__.recvfrom_into(buffView)
                buffView = buffView[received:]
                segment = self.buffer[offset:offset+received]
                args = SocketDataEventArgs(sender, socket, segment)
                offset += received
                if(self.debug):
                    print("socket system - data received: \n\tsocket: {}\n\tdata: {}".format(socket, args))
                self.onData.Invoke(args)

    def __del__(self):
        for s in self.sockets:
            s.__socket__.close()
            if(self.debug):
                print("socket system - socket closed: {}".format(s.localEndPoint))
