from restServer.requestHandler import RequestHandler
# from restServer/RequestHandler import RequestHandler

import time
from http.server import HTTPServer
import debug

HOST_NAME = '0.0.0.0'
PORT_NUMBER = 5000

# debug.pc_print('program initializing')


class RestServer():
    def __init__(self, port):
        # print('server intialized')
        self.requestHandler = RequestHandler
        self.port = port

    def Run(self):
        httpd = HTTPServer((HOST_NAME, PORT_NUMBER), self.requestHandler)

        debug.pc_print('Server UP special - %s:%s' % (HOST_NAME, PORT_NUMBER))
        # print(time.asctime(), 'Server UP - %s:%s' % (HOST_NAME, PORT_NUMBER))

        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            pass

        httpd.server_close()
        debug.pc_print('Server DOWN special - %s:%s' % (HOST_NAME, PORT_NUMBER))
        # print(time.asctime(), 'Server DOWN - %s:%s' % (HOST_NAME, PORT_NUMBER))


if __name__ == '__main__':
    @staticmethod
    def OnRequest(path):
        print("request callback not set")
        return "request callback not set\npath: " + path
    server = RestServer(5000)
    server.requestHandler.onRequestCallback = OnRequest
    server.Run()
