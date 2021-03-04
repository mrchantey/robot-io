from Messages.Message import Message
from enum import Enum
import struct
from Ahoy.AhoyList import Insert


class DataType(Enum):
    NoType = 1
    Float = 2


def HeadersToBytes(channel, command):
    arr = bytearray([channel, command, DataType.NoType.value])
    return arr


def BytesToFloats(barr):
    lenFarr = int(len(barr) / 4)
    farr = [None] * lenFarr
    for fi in range(lenFarr):
        bi = fi * 4
        farr[fi] = struct.unpack('<f', barr[bi:bi+4])[0]
    return farr


def BytesToMessage(barr):

    dataType = DataType(barr[2])
    bdata = barr[3:]
    if(dataType == DataType.NoType):
        return Message(barr[0], barr[1], dataType, None)
    elif(dataType == DataType.Float):
        fdata = BytesToFloats(bdata)
        return Message(barr[0], barr[1], dataType, fdata)
    return Message(barr[0], barr[1], dataType, None)


def FloatMessageToBytes(msg):
    channel = msg.channel
    command = msg.command
    arr = msg.data
    if not isinstance(arr, list):
        arr = [arr]
    arrLen = len(arr)
    headerLen = 3
    bodyLen = arrLen * 4
    totalLen = headerLen + bodyLen
    bArr = bytearray(totalLen)

    bArr[0] = channel
    bArr[1] = command
    bArr[2] = DataType.Float.value
    for ai in range(arrLen):
        bi = headerLen + ai * 4
        bv = bytes(struct.pack("<f", arr[ai]))
        Insert(bArr, bv, bi)
    return bArr


def MessageToBytes(msg):
    if(msg.dataType == DataType.NoType):
        return HeadersToBytes(msg.channel, msg.command)
    elif(msg.dataType == DataType.Float):
        return FloatMessageToBytes(msg)
