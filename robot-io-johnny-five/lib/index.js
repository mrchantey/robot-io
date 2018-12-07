"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;

var _johnnyFiveInterface = _interopRequireDefault(require("./johnny-five-interface"));

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var _default = createJohnnyFiveMiddleware;
exports.default = _default;
module.exports = createJohnnyFiveMiddleware;

const argvIn = require('minimist')(process.argv.slice(2));

const argv = {};
Object.assign(argv, argvIn);

function createJohnnyFiveMiddleware() {
  const johhnyFiveInterface = (0, _johnnyFiveInterface.default)(argv);
  const onDataListeners = [];
  const onData = {
    addListener: listener => onDataListeners.push(listener),
    invoke: data => onDataListeners.forEach(l => l(data))
  };
  johhnyFiveInterface.onDataCallback = onData.invoke;

  if (argv.debug === true) {
    onData.addListener(data => {
      console.log('data received');
      console.dir(data);
    });
  }

  const middleware = {
    onData,
    johhnyFiveInterface,
    sendData: johhnyFiveInterface.sendData
  };
  return middleware;
}

if (require.main === module) {
  createJohnnyFiveMiddleware();
}