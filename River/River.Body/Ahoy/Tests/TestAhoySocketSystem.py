import unittest
from Sockets.Systems import socketSystem


class TestSocketSystem(unittest.TestCase):

    def testCreateSocket(self):
        socket = socketSystem.CreateSocket(5000)
        self.assertEqual(str(socket), "127.0.0.1:5000")

    def testSendReceive(self):
        socket1 = socketSystem.CreateSocket(5001)
        socket2 = socketSystem.CreateSocket(5002)
        socketSystem.Connect(socket2, socket1.localEndPoint)
        data = bytearray([0, 1, 2, 3])

        self.dataReceived = False

        def onReceiveData(args):
            self.dataReceived = True
            # print('data received: {}'.format(args))
            self.assertEqual(len(args.data), len(data))

        socketSystem.onData.AddListener(onReceiveData)
        socketSystem.SendData(socket2, data)

        while self.dataReceived == False:
            # print("updating system")
            socketSystem.Update()


if __name__ == '__main__':
    try:
        unittest.main()
    except KeyboardInterrupt:
        pass
