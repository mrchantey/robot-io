import unittest
from Messages.Message import Message
from Messages import MessageUtility
from Ahoy.AhoyList import EqualElements, AlmostEqualElements
# from Ahoy import Systems


class TestMessageUtility(unittest.TestCase):

    def testHeadersToBytes(self):
        arrBytes = MessageUtility.HeadersToBytes(68, 32)
        correctArr = bytearray([68, 32, 1])

        self.assertTrue(EqualElements(arrBytes, correctArr))

    def testHeaderMessageToBytes(self):
        msg1 = Message(59, 32, MessageUtility.DataType.NoType, None)
        barr = MessageUtility.MessageToBytes(msg1)
        msg2 = MessageUtility.BytesToMessage(barr)

        self.assertEqual(msg1.channel, msg2.channel)
        self.assertEqual(msg1.command, msg2.command)

    def testFloatMessageToBytes(self):
        farr1 = [5.73, 9.8434980]
        msg1 = Message(59, 32, MessageUtility.DataType.Float, farr1)
        barr = MessageUtility.MessageToBytes(msg1)

        msg2 = MessageUtility.BytesToMessage(barr)

        self.assertEqual(msg1.channel, msg2.channel)
        self.assertEqual(msg1.command, msg2.command)

        self.assertTrue(AlmostEqualElements(msg1.data, msg2.data))


if __name__ == '__main__':
    unittest.main()
