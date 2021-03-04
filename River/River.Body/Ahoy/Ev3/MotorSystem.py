from Messages.Systems import messageReceiveSystem
import ev3dev2
from ev3dev2 import motor
from ev3dev2 import port
from .FakeMotor import FakeMotor

from enum import Enum


class MotorType(Enum):
    NotConnected = 1
    Large = 2
    Medium = 3


class MotorSystem():
    def __init__(self, type1=MotorType.Medium, type2=MotorType.Large, type3=MotorType.Large, type4=MotorType.NotConnected):
        messageReceiveSystem.AddChannelListener(32, self.OnMessage)
        self.percentScalar = 100
        self.InitMotor1(type1)
        self.InitMotor2(type2)
        self.InitMotor3(type3)
        self.InitMotor4(type4)
        self.commandLookup = {
            0: lambda floats: self.SetMotor(self.motor1, floats[0]),
            1: lambda floats: self.SetMotor(self.motor2, floats[0]),
            2: lambda floats: self.SetMotor(self.motor3, floats[0]),
            3: lambda floats: self.SetMotor(self.motor4, floats[0]),
            4: lambda floats: self.SetMotors([self.motor1, self.motor2], floats),
            5: lambda floats: self.SetMotors([self.motor1, self.motor3], floats),
            6: lambda floats: self.SetMotors([self.motor1, self.motor4], floats),
            7: lambda floats: self.SetMotors([self.motor2, self.motor3], floats),
            8: lambda floats: self.SetMotors([self.motor2, self.motor4], floats),
            9: lambda floats: self.SetMotors([self.motor3, self.motor4], floats),
            10: lambda floats: self.SetMotors([self.motor1, self.motor2, self.motor3], floats),
            11: lambda floats: self.SetMotors([self.motor1, self.motor2, self.motor4], floats),
            12: lambda floats: self.SetMotors([self.motor2, self.motor3, self.motor4], floats),
            13: lambda floats: self.SetMotors([self.motor1, self.motor2, self.motor3, self.motor4], floats)
        }

    def InitMotor1(self, motorType):
        self.motor1 = self.InitMotor(motorType, motor.OUTPUT_A)

    def InitMotor2(self, motorType):
        self.motor2 = self.InitMotor(motorType, motor.OUTPUT_B)

    def InitMotor3(self, motorType):
        self.motor3 = self.InitMotor(motorType, motor.OUTPUT_C)

    def InitMotor4(self, motorType):
        self.motor4 = self.InitMotor(motorType, motor.OUTPUT_D)

    def InitMotor(self, motorType, port):
        if(motorType == MotorType.Medium):
            return motor.MediumMotor(port)
        elif(motorType == MotorType.Large):
            return motor.LargeMotor(port)
        else:
            return FakeMotor()

    def InvertDirection(self):
        self.percentScalar = self.percentScalar * -1

    def OnMessage(self, args):
        command = self.commandLookup.get(args.message.command)
        if(command == None):
            print("Ev3 - invalid command: {}".format(command))
        else:
            command(args.message.data)

    def SetMotor(self, motor, normalVal):
        speed = normalVal * self.percentScalar
        print("setting motor {} to {}".format(motor, speed))
        motor.on(speed)

    def SetMotors(self, motors, normalSpeeds):
        for i in range(len(motors)):
            speed = normalSpeeds[i] * self.percentScalar
            motors[i].on(speed)


# if __name__ == "__main__":
#     print()
    # try:
    # except:
    #     pass
    # print(ev3dev2.port.LegoPort())
