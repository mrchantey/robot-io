"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;

const five = require('johnny-five');

const avrGirl = require('avrgirl-arduino');

module.exports = createJFiveInterface;
var _default = createJFiveInterface;
exports.default = _default;

function createJFiveInterface() {
  let argv = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : {};
  const j5 = {
    onDataCallback(data) {
      console.log('data emitted');
      console.dir(data);
    },

    sendData(data) {
      if (argv.debug === true) console.log('sending data not yet supported');
    }

  };
  createBoard(argv.serialPort).then(board => {
    board.on("error", console.error);
    board.on("ready", _ => {
      const imu = new five.IMU({
        controller: "MPU6050"
      });
      const initData = {
        init: [{
          type: "chart",
          name: "Accelerometer",
          id: 0
        }, {
          type: "trace",
          name: "x",
          id: 1,
          chartId: 0
        }, {
          type: "trace",
          name: "y",
          id: 2,
          chartId: 0
        }, {
          type: "trace",
          name: "z",
          id: 3,
          chartId: 0
        }, {
          type: "chart",
          name: "Gyroscope",
          id: 1
        }, {
          type: "trace",
          name: "x",
          id: 4,
          chartId: 1
        }, {
          type: "trace",
          name: "y",
          id: 5,
          chartId: 1
        }, {
          type: "trace",
          name: "z",
          id: 6,
          chartId: 1
        }]
      };
      j5.onDataCallback(initData);
      const acc = imu.accelerometer;
      const gyro = imu.gyro;
      const startMillis = Date.now();
      let lastMillis = Date.now();
      imu.on("data", _ => {
        const millis = Date.now();
        const deltaMillis = millis - lastMillis;
        let timeStamp = (millis - startMillis) / 1000; //WAIT (non blocking) at least 50ms delta time

        if (deltaMillis > 50) {
          const newData = {
            timeStamp,
            data: [{
              id: 1,
              value: acc.x
            }, {
              id: 2,
              value: acc.y
            }, {
              id: 3,
              value: acc.z
            }, {
              id: 4,
              value: gyro.x
            }, {
              id: 5,
              value: gyro.y
            }, {
              id: 6,
              value: gyro.z
            }]
          };
          j5.onDataCallback(newData);
          lastMillis = millis;
        }
      });
    });
  });
  return j5;
}

async function createBoard(port) {
  if (port === undefined) port = await getDefaultPort();
  return new five.Board({
    port
  });
}

function getDefaultPort() {
  return new Promise((resolve, reject) => {
    avrGirl.list((err, ports) => {
      const port = ports.find(p => p.manufacturer === 'Arduino LLC (www.arduino.cc)');

      if (port === undefined) {
        reject('no arduinos found, pleas specify port name\nexample:\nnode lib/test.js  --port COM3');
      } else {
        resolve(port.comName);
      }
    });
  });
}

if (require.main === module) {
  // const j5 = createJFiveInterface({ serialPort: "COM7" })
  const j5 = createJFiveInterface();
} // Can also be written as: 
// const sensor = new five.Sensor.Digital(7);
// sensor.on('data', console.log)
// board.pinMode(13, five.Pin.OUTPUT)
// board.pinMode(7, five.Pin.INPUT)
// board.digitalRead(7, console.log)
// let isOn = false
// setInterval(() => {
// isOn = !isOn
// board.digitalWrite(13, isOn ? 1 : 0)
// board.digitalRead(13, console.log);
// }, 1000);