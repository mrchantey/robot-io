import unittest
from Ahoy.AhoyList import AlmostEqualElements
from Messages.Message import Message
from Messages import MessageUtility
from Messages.Systems import messageReceiveSystem
# from Ahoy import Systems
from Sockets.SocketDataEventArgs import SocketDataEventArgs


class TestMessageUtility(unittest.TestCase):

    def testMessageReceive(self):
        farr1 = [0.342, 0.4389090]
        msg1 = Message(69, 32, MessageUtility.DataType.Float, farr1)
        bytes1 = MessageUtility.MessageToBytes(msg1)
        socketDataArgs = SocketDataEventArgs(None, None, bytes1)

        def OnMessage(args):
            print("OK - on message called")
            self.assertTrue(AlmostEqualElements(farr1, args.message.data))

        messageReceiveSystem.AddChannelListener(69, OnMessage)
        messageReceiveSystem.OnData(socketDataArgs)


if __name__ == '__main__':
    unittest.main()
