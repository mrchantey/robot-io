from droidMessage import utility


def Decorate(obj):
    pokeHeader = bytes([obj.channel, 0])
    pokeReplyHeader = bytes([obj.channel, 1])

    def HandleReceive(header, body):
        if(utility.AllEqual(header, pokeHeader)):
            ReceivePoke(body)
            return True
        elif(utility.AllEqual(header, pokeReplyHeader)):
            ReceivePokeReply(body)
            return True
        else:
            return False

    def SendPoke():
        msg = pokeHeader\
            .__add__(obj.addressBytes)
        obj.onSendBytes(msg)

    def SendPokeReply():
        msg = pokeReplyHeader\
            .__add__(obj.addressBytes)
        obj.onSendBytes(msg)

    def ReceivePoke(msg):
        obj.onPoke()
        SendPokeReply()

    def ReceivePokeReply(msg):
        ipAddress, port = utility.BytesToIpAndPort(msg)
        obj.onPokeReply(ipAddress, port)

    obj.onPoke = lambda _: print("on poke callback")
    obj.onPokeReply = lambda ip, port: print("on poke reply callback")
    obj.receiveHandlers.append(HandleReceive)
    obj.SendPoke = SendPoke
