from droidMessage import utility


def Decorate(obj):
    setLRHeader = bytes([obj.channel, 24])
    setAux1Header = bytes([obj.channel, 27])

    def HandleReceive(header, body):
        if(utility.AllEqual(header, setLRHeader)):
            ReceiveSetLRMotors(body)
            return True
        elif(utility.AllEqual(header, setAux1Header)):
            ReceiveSetAux1Motor(body)
        else:
            return False

    def SendSetLRMotors(left, right):
        bLeft = utility.FloatToBytes(left)
        bRight = utility.FloatToBytes(right)
        msg = setLRHeader\
            .__add__(bLeft)\
            .__add__(bRight)
        obj.onSendBytes(msg)

    def SendSetAux1Motor(val):
        bVal = utility.FloatToBytes(val)
        msg = setAux1Header\
            .__add__(bVal)
        obj.onSendBytes(msg)

    def ReceiveSetLRMotors(bMsg):
        fLeft = utility.BytesToFloat(bMsg[:4])
        fRight = utility.BytesToFloat(bMsg[4:8])
        obj.onSetLRMotors(fLeft, fRight)

    def ReceiveSetAux1Motor(bMsg):
        fVal = utility.BytesToFloat(bMsg[:4])
        obj.onSetAux1Motor(fVal)

    obj.onSetLRMotors = lambda left, right: print("left right motors callback L:{},R:{}".format(left, right))
    obj.onSetAux1Motor = lambda val: print("Set aux motor callback: {}".format(val))
    obj.SendSetLRMotors = SendSetLRMotors
    obj.SendSetAux1Motor = SendSetAux1Motor
    obj.receiveHandlers.append(HandleReceive)
