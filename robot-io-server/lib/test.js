"use strict";

var _index = _interopRequireDefault(require("./index"));

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

const robotIO = (0, _index.default)();
testSendData();

function testSendData() {
  const startMillis = Date.now();
  setInterval(() => {
    robotIO.server.sendData({
      mpu: {
        acc: {
          x: Math.random(),
          y: Math.random(),
          z: Math.random()
        },
        gyro: {
          x: Math.random(),
          y: Math.random(),
          z: Math.random()
        }
      },
      timeStamp: Date.now() - startMillis
    });
  }, 100);
}