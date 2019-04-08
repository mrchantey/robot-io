
from ev3dev2 import motor as eMotor
import debug_ev3


class NeckMotor():

    def __init__(self, portName):
        self.motor = eMotor.MediumMotor(eMotor.OUTPUT_D)
        self.PrintPosition()
        self.motor.reset()
        self.PrintPosition()
        self.speed = 10
        self.maxAngle = 45

    def Start(self):
        self.motor.on(eMotor.SpeedPercent(self.speed))

    def Update(self):
        if self.motor.position < -self.maxAngle:
            self.motor.on(eMotor.SpeedPercent(self.speed))
        elif self.motor.position > self.maxAngle:
            self.motor.on(eMotor.SpeedPercent(-self.speed))
        self.PrintPosition()

    def End(self):
        while(self.motor.position != 0):
            self.motor.run_to_abs_pos(position_sp=0, speed_sp=100)
            # self.PrintPosition("returning neck motor to initial position")
        debug_ev3.pc_print("neck motor returned to original position")

    def PrintPosition(self, prefix="neck motor position"):
        debug_ev3.pc_print(prefix + " : " + str(self.motor.position))
