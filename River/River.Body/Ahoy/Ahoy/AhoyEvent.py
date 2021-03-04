from Ahoy.AhoyList import AhoyList


class AhoyEvent():
    def __init__(self):
        self.listeners = AhoyList()
        # self.listeners.TryAdd()

    def AddListener(self, listener):
        self.listeners.TryAdd(listener)

    def removeListener(self, listener):
        self.listeners.TryRemove(listener)

    def Invoke(self, args):
        for l in self.listeners:
            l(args)
