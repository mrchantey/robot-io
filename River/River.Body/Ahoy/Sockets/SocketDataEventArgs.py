

class SocketDataEventArgs():
    def __init__(self, sender, receiver, data):
        self.sender = sender
        self.receiver = receiver
        self.data = data

    def __str__(self):
        return "sender: {}, receiver: {}, data length: {} data: {}".format(self.sender, self.receiver, len(self.data), self.data)
# $"receiver: {receiver}, sender:{sender}, data length:{data.Count}, data:{data.ElementsToString()}";
