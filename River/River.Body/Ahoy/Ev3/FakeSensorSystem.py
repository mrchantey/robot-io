from Sockets.Systems import socketSystem
from Messages import Message, MessageUtility
import random


class FakeSensorSystem():
    def __init__(self):
        pass

    def SendSensorInfo(self, socket):
        val = float(random.randint(0, 255))
        # data = bytearray([val])
        msg = Message.Message(33, 0, MessageUtility.DataType.Float, [val])
        data = MessageUtility.FloatMessageToBytes(msg)
        socketSystem.SendData(socket, data)
