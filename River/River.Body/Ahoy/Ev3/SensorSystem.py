#!/usr/bin/env python3

# from Messages.Systems import messageReceiveSystem
import ev3dev2.sensor
from ev3dev2.sensor import lego
from enum import Enum
from Sockets.Systems import socketSystem
from Messages import Message, MessageUtility


class SensorSystem():
    def __init__(self):
        # port 4
        self.ultrasonicSensor = lego.UltrasonicSensor(ev3dev2.sensor.INPUT_4)

    def SendSensorInfo(self, socket):
        val = float(self.ultrasonicSensor.distance_centimeters)
        # val = self.ultrasonicSensor.distance_centimeters_continuous
        msg = Message.Message(33, 0, MessageUtility.DataType.Float, [val])
        data = MessageUtility.FloatMessageToBytes(msg)
        socketSystem.SendData(socket, data)
        pass

    def OnMessage(self, args):
        pass


if __name__ == "__main__":
    print("hello world")
    # try:
    # except:
    #     pass
    # print(ev3dev2.port.LegoPort())
