from http.server import BaseHTTPRequestHandler
import debug
import json


class RequestHandler(BaseHTTPRequestHandler):
    # def __init__(self, onRequestCallback):
    #     super(RequestHandler, self).__init__()
    #     # BaseHTTPRequestHandler.__init__()
    #     self.onRequestCallback = onRequestCallback
    # # def __init__(self):
    # #     self.onRequestCallback = OnRequest
    # #     pass

    def do_GET(self):
        debug.pc_print('GET request path:', self.path)
        print("bangGet")
        self.send_response(200)
        # self.send_header('Content-Type', 'text/html')
        self.send_header('Content-Type', 'application/json')
        self.end_headers()
        responseDict = self.onRequestCallback(self.path)
        responseStr = json.dumps(responseDict)
        responseBytes = bytes(responseStr, "UTF-8")
        self.wfile.write(responseBytes)
        return
    # 3

    # this should be called for preflight responses
    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        # self.send_header('Access-Control-Allow-Credentials', 'true')
        self.send_header('Access-Control-Allow-Headers', 'X-Requested-With')
        self.send_header('Access-Control-Allow-Methods', 'POST, GET, OPTIONS')
        # 24hr validation of preflight
        self.send_header('Access-Control-Max-Age', 86400)
        BaseHTTPRequestHandler.end_headers(self)
