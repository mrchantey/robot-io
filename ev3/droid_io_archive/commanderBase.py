
class CommanderBase():
    def __init__(self):
        pass

    def printargs(self, **kwargs):
        for key, value in kwargs.items():
            print(key, value)

    def Run(self, command, **kwargs):
        getattr(self, command)(**kwargs)


if __name__ == '__main__':
    commander = CommanderBase()
    command = {
        'command': 'printargs',
        'name': 'Marvel',
        'isAwesome': True,
        'numberOfKittens': 49
    }

    commander.Run(**command)
