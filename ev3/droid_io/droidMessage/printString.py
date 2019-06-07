from droidMessage import utility


def Decorate(obj):
    printStringHeader = bytes([obj.channel, 16])

    def HandleReceive(header, body):
        if(utility.AllEqual(header, printStringHeader)):
            ReceivePrintString(body)
            return True
        else:
            return False

    def SendPrintString(str):
        bStr = bytes(str, 'utf-8')
        strLen = len(bStr)
        bLen = utility.IntToBytes(strLen)
        msg = printStringHeader\
            .__add__(bLen)\
            .__add__(bStr)
        obj.onSendBytes(msg)

    def ReceivePrintString(bMsg):
        sLen = utility.BytesToInt(bMsg[:4])
        sMsg = bMsg[4:4+sLen].decode('utf-8')
        obj.onPrintString(sMsg)

    obj.onPrintString = lambda message: print("print callback:" + message)
    obj.SendPrintString = SendPrintString
    obj.receiveHandlers.append(HandleReceive)
