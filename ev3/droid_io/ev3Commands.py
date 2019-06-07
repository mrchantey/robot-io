
from ev3dev2 import motor


def Decorate(obj, invertDirection):
    percentScalar = 100
    if(invertDirection):
        percentScalar = percentScalar * -1
    motorsLR = motor.MoveTank(motor.OUTPUT_B, motor.OUTPUT_C)
    motorL = motor.LargeMotor(motor.OUTPUT_B)
    motorR = motor.LargeMotor(motor.OUTPUT_C)
    motorAux1 = motor.MediumMotor(motor.OUTPUT_A)

    def SetLRMotors(left, right):
        leftPercent = left * percentScalar
        rightPercent = right * percentScalar
        motorsLR.on(leftPercent, rightPercent)

    def SetAux1Motor(val):
        percent = val * percentScalar
        motorAux1.on(percent)

    def StopAll():
        motorsLR.off()
        motorAux1.off()

    obj.onSetLRMotors = SetLRMotors
    obj.onSetAux1Motor = SetAux1Motor
    obj.stopHandlers.append(StopAll)

    # def StopAll()
