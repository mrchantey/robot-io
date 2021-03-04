

class AhoyList(list):
    def __init__(self):
        pass

    def TryAdd(self, item):
        if item in self:
            return False
        else:
            self.append(item)
            return True

    def TryRemove(self, item):
        if not item in self:
            return False
        else:
            self.remove(item)
            return True

    # def ForEach(self,item):


def EqualElements(arr1, arr2):
    len1 = len(arr1)
    len2 = len(arr2)
    if(len1 != len2):
        # print("lengths not equal")
        return False

    for i in range(len1):
        if arr1[i] != arr2[i]:
            # print("values not equal: {}, {}".format(arr1[i], arr2[i]))
            return False
    return True


def AlmostEqualElements(arr1, arr2, tolerance=0.001):
    len1 = len(arr1)
    len2 = len(arr2)
    if(len1 != len2):
        return False

    for i in range(len1):
        if abs(arr1[i] - arr2[i]) > tolerance:
            return False
    return True


def Insert(arr1, arr2, offset):
    for i2 in range(0, len(arr2)):
        i1 = i2 + offset
        arr1[i1] = arr2[i2]
