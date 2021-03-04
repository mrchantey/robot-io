from Messages.Systems import messageReceiveSystem


class FakeMotorSystem():
    def __init__(self):
        messageReceiveSystem.AddChannelListener(32, self.OnMessage)
        self.percentScalar = 100
        self.motor1 = "motor.MediumMotor(motor.OUTPUT_A)"
        self.motor2 = "motor.LargeMotor(motor.OUTPUT_B)"
        self.motor3 = "motor.LargeMotor(motor.OUTPUT_C)"
        self.motor4 = "motor.MediumMotor(motor.OUTPUT_C)"
        self.motors14 = 'motor.MoveTank(motor.OUTPUT_A, motor.OUTPUT_D)'
        self.motors23 = 'motor.MoveTank(motor.OUTPUT_B, motor.OUTPUT_C)'
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
        pass

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

    def SetMotors(self, motors, normalSpeeds):
        for i in range(len(motors)):
            speed = normalSpeeds[i] * self.percentScalar
            print("setting motor {} to {}".format(motors[i], speed))
