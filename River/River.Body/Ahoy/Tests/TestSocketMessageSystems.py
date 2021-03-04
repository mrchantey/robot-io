import unittest
from Sockets.Systems import socketSystem
from Messages.Systems import messageReceiveSystem
from Messages.Message import Message
from Messages import MessageUtility
from Ahoy.AhoyList import AlmostEqualElements


class TestSocketSystem(unittest.TestCase):

    def testSocketMessages(self):
        socket1 = socketSystem.CreateSocket(5001)
        socket2 = socketSystem.CreateSocket(5002)
        socketSystem.Connect(socket2, socket1.localEndPoint)

        farr1 = [-329.3223, 8343.32]
        msg1 = Message(69, 32, MessageUtility.DataType.Float, farr1)

        def MessageReceived(args):
            print("message received: {}".format(args))
            self.assertEqual(args.receiver.localEndPoint, socket1.localEndPoint)
            self.assertEqual(args.sender, socket2.localEndPoint)
            self.assertEqual(msg1.channel, args.message.channel)
            self.assertEqual(msg1.command, args.message.command)
            self.assertTrue(AlmostEqualElements(msg1.data, args.message.data, 0.001))

        messageReceiveSystem.AddChannelListener(69, MessageReceived)

        barr1 = MessageUtility.MessageToBytes(msg1)
        socketSystem.SendData(socket2, barr1)
        socketSystem.Update()


if __name__ == '__main__':
    try:
        unittest.main()
    except KeyboardInterrupt:
        pass
