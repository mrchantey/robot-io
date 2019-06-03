#!/usr/bin/env python3
from server import Server
from utility import Utility
from commanderBase import CommanderBase
from ev3Commander import Ev3Commander
import sys

isDeployed = True


def GetIsDeployed():
    if(isDeployed == True):
        return True
    if len(sys.argv) <= 1:
        return False
    if(sys.argv[1] != 'true'):
        return False
    return True


def GetCommander():
    if(GetIsDeployed()):
        return Ev3Commander()
    else:
        return CommanderBase()


if __name__ == '__main__':
    print("program running...")
    server = Server(5000)
    commander = GetCommander()
    @staticmethod
    def onRequest(path):
        kwargs = Utility.ParseURL(path)
        commander.Run(**kwargs)
        return kwargs
    server.requestHandler.onRequestCallback = onRequest
    server.Run(GetIsDeployed())
