
from ev3dev2.sensor import lego, INPUT_2


class DepthSensor:
    def __init__(self):
        self.sensor = lego.UltrasonicSensor(INPUT_2)
        # self.sensor.mode = 'US-DIST-CM'
        # self.sensor.

    def GetReading(self):
        return self.sensor.distance_centimeters_continuous / 10
        # return self.sensor.value() / 10
