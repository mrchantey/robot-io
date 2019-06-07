import json


class Utility():

    @staticmethod
    def ParseURL(urlPath):
        cleanPath = urlPath.replace("/", "")
        kwargs = cleanPath.split(",")
        print("kwargs:", kwargs)
        kwargDict = {}
        for kwarg in kwargs:
            print("kwarg", kwarg)
            kvp = kwarg.split(":")
            kwargDict[kvp[0]] = Utility.ParseValue(kvp[1])
        return kwargDict
        # testClass[](kwargDict)

    @staticmethod
    def ParseValue(val):
        try:
            iVal = int(val)
            return iVal
        except ValueError:
            pass
        try:
            fVal = float(val)
            return fVal
        except ValueError:
            pass
        if val == 'true'or val == 'True':
            return True
        elif val == 'false' or val == 'False':
            return False
        return val


if __name__ == '__main__':
    myString = "/command:playtone,frequency:480"
    kwargDict = Utility.ParseURL(myString)
    for key, value in kwargDict.items():
        print(key, value)
    # getattr(testClass, kwargDict["command"])(**kwargDict)
