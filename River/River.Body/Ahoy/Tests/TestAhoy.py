import unittest
import Ahoy
from Ahoy.AhoyList import AhoyList
from Ahoy.AhoyEvent import AhoyEvent
# from Sockets.AhoySocket import AhoySocket


class TestAhoySocket(unittest.TestCase):

    def testAhoyList(self):
        lst = AhoyList()
        val = "hi"
        self.assertTrue(lst.TryAdd(val))
        self.assertFalse(lst.TryAdd(val))

    def testAhoyEvent(self):
        eve = AhoyEvent()

        self.val1 = 0

        def setval(val2):
            self.val1 = val2
        eve.AddListener(setval)
        eve.Invoke(439)
        self.assertEqual(self.val1, 439)


if __name__ == '__main__':
    unittest.main()
