# tank_drive = MoveTank(OUTPUT_B, OUTPUT_C)
# tank_drive.on(SpeedPercent(speed), SpeedPercent(speed))

from ev3dev2 import motor as eMotor


class Tank:
    def __init__(self, speed=50):
        self.tank = eMotor.MoveTank(eMotor.OUTPUT_B, eMotor.OUTPUT_C)
        self.speed = speed

    def Forward(self):
        self.tank.on(eMotor.SpeedPercent(self.speed),
                     eMotor.SpeedPercent(self.speed))

    def Turn(self):
        self.tank.on(eMotor.SpeedPercent(self.speed),
                     eMotor.SpeedPercent(-self.speed))
