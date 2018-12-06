"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;

var _server = _interopRequireDefault(require("./server"));

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

const argvIn = require('minimist')(process.argv.slice(2));

const argv = Object.assign({
  port: 3000,
  hostname: "127.0.0.1"
}, argvIn);
var _default = createRobotIO;
exports.default = _default;
module.exports = createRobotIO;

function createRobotIO() {
  const server = (0, _server.default)(argv);
  const robotIO = {
    server
  };

  function addMiddleware(middleware) {
    server.onData.addListener(middleware.sendData);
    middleware.onData.addListener(server.sendData);
  }

  return robotIO;
}