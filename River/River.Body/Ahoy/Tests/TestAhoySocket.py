import unittest
from Sockets.AhoySocket import AhoySocket


class TestAhoySocket(unittest.TestCase):

    def testString(self):
        socket = AhoySocket(5000)
        self.assertEqual(str(socket), "0.0.0.0:5000")


if __name__ == '__main__':
    # print("running")
    unittest.main()
