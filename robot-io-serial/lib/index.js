"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;

require("core-js/modules/web.dom.iterable");

var _jsonBufferParser = _interopRequireDefault(require("./jsonBufferParser"));

var _serialIO = _interopRequireDefault(require("./serialIO"));

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var _default = createRobotSerial;
exports.default = _default;
module.exports = createRobotSerial;

function createRobotSerial() {
  const serialIO = (0, _serialIO.default)();
  const jsonBufferParser = (0, _jsonBufferParser.default)();
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
  return robotSerial;
}