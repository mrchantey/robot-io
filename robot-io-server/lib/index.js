"use strict";

var _react = _interopRequireDefault(require("react"));

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

console.log(_react.default); // const argvIn = require('minimist')(process.argv.slice(2));
// import Server from './server';
// const argv = Object.assign({ port: 3000, hostname: "127.0.0.1" }, argvIn)
// const server = Server(argv)
// testSendData()
// function testSendData() {
//     const startMillis = Date.now()
//     setInterval(() => {
//         server.sendData({
//             mpu: {
//                 acc: {
//                     x: Math.random(),
//                     y: Math.random(),
//                     z: Math.random()
//                 },
//                 gyro: {
//                     x: Math.random(),
//                     y: Math.random(),
//                     z: Math.random()
//                 }
//             },
//             timeStamp: Date.now() - startMillis
//         })
//     }, 100);
// }
// const server = Server(argv)