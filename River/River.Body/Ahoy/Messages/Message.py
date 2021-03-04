

class Message():
    def __init__(self, channel, command, dataType, data):
        self.channel = channel
        self.command = command
        self.dataType = dataType
        self.data = data

    def __str__(self):
        return "channel: {}, command: {}, data type: {}, data length: {} data: {}".format(self.channel, self.command, self.dataType, len(self.data), self.data)
