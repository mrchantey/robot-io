floatMultiplier = 1000000000
#                 b  m  t   1 billion
floatDivider = 0.000000001
# hfloatMultiplier = floatMultiplier/2
# hFloatMul = 500000000
#          b  m  t   1 billion


def IntToBytes(val):
    return val.to_bytes(4, 'little')


def BytesToInt(val):
    return int.from_bytes(val, 'little')


def FloatToBytes(val):
    val = (int)(val * floatMultiplier) + floatMultiplier
    return val.to_bytes(4, 'little')


def BytesToFloat(val):
    vInt = int.from_bytes(val, 'little')
    return (vInt - floatMultiplier) * floatDivider


def IpToBytes(ipAddress):
    strIp = ipAddress.split('.')
    intIp = map(lambda s: int(s), strIp)
    return bytes(intIp)


def BytesToIp(bIp):
    sIp = map(lambda b: str(b), bIp)
    ip = '.'.join(sIp)
    return ip


def BytesToIpAndPort(msg):
    ipAddress = BytesToIp(msg[:4])
    port = BytesToInt(msg[4:8])
    return (ipAddress, port)


def AllEqual(arr1, arr2):
    if(len(arr1) != len(arr2)):
        return False
    isEqual = True
    for i in range(len(arr1)):
        if(arr1[i] != arr2[i]):
            isEqual = False
    return isEqual


if __name__ == '__main__':
    val = 0.01234567890
    valBytes = FloatToBytes(val)
    valInt = BytesToFloat(valBytes)
    print(valInt)
    # print(IntToBytes(val))
    # arr1 = [43, 43, 43, 43]
    # arr2 = [43, 43, 43]
    # print(AllEqual(arr1, arr2))
