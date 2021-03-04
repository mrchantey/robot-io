

class MessageEventArgs():
    def __init__(self, sender, receiver, message):
        self.sender = sender
        self.receiver = receiver
        self.message = message

    def __str__(self):
        return "sender: {}, receiver: {}, message: \n{}".format(self.sender, self.receiver,  self.message)
# $"receiver: {receiver}, sender:{sender}, data length:{data.Count}, data:{data.ElementsToString()}";
