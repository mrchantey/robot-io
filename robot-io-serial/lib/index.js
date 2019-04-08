"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;

require("core-js/modules/web.dom.iterable");

var _jsonBufferParser = _interopRequireDefault(require("./jsonBufferParser"));

var _serialIO = _interopRequireDefault(require("./serialIO"));

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

const argvIn = require('minimist')(process.argv.slice(2));

const argv = {
  serialPort: "COM7",
  baudRate: 115200
};
Object.assign(argv, argvIn);
var _default = createRobotSerial;
exports.default = _default;
module.exports = createRobotSerial;

function createRobotSerial() {
  const serialIO = (0, _serialIO.default)(argv);
  const jsonBufferParser = (0, _jsonBufferParser.default)(argv);
  serialIO.onBufferCallback = jsonBufferParser.parseBuffer;

  jsonBufferParser.onDataCallback = data => onDataListeners.forEach(l => l(data));

  const onDataListeners = [];
  const onData = {
    addListener: listener => onDataListeners.push(listener)
  };
  const robotSerial = {
    serialIO,
    jsonBufferParser,
    onData,
    sendData: data => serialIO.sendData(JSON.stringify(data))
  };

  if (argv.debug === true) {
    console.log('\ndebug mode enabled\n');
    robotSerial.onData.addListener(data => {
      console.log('data received');
      console.dir(data);
    });
  }

  return robotSerial;
}

if (require.main === module) {
  createRobotSerial();
}