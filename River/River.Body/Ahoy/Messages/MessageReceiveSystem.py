from Ahoy.AhoyEvent import AhoyEvent
from Sockets.Systems import socketSystem
from Messages import MessageUtility, MessageEventArgs


class MessageReceiveSystem():
    def __init__(self):
        socketSystem.onData.AddListener(self.OnData)
        self.channelEvents = {}

    def GetOrCreateChannelReceiver(self, key):
        eve = self.channelEvents.get(key)
        if eve == None:
            eve = AhoyEvent()
        self.channelEvents[key] = eve
        return eve

    def AddChannelListener(self, channel, onMessage):
        eve = self.GetOrCreateChannelReceiver(channel)
        eve.AddListener(onMessage)

    def OnData(self, args):
        eve = self.channelEvents.get(args.data[0])
        if(eve == None):
            return
        # print("channel {}".format(args.data[0]))
        msg = MessageUtility.BytesToMessage(args.data)
        msgArgs = MessageEventArgs.MessageEventArgs(args.sender, args.receiver, msg)
        eve.Invoke(msgArgs)
