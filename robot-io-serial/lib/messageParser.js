"use strict";

const mpuParser = require('../archive/server/mpuParser');

const dataParser = require('../archive/server/dataParser'); //TODO RENAME AS BUFFER PARSER


module.exports = {
  onMessageCallback,
  parseMessage
};
let message = "";
let isProcessingMessage = false;

function onMessageCallback(obj) {
  console.dir(obj);
}

function parseMessage(msg) {
  for (let i = 0; i < msg.length; i++) {
    const chr = msg.charAt(i);
    if (chr === '<') isProcessingMessage = true;else if (isProcessingMessage && chr === '>') onMessageComplete(message);else if (isProcessingMessage) message += chr;
  }
}

function onMessageComplete(msg) {
  // console.log('message complete');
  // console.log(msg);
  message = "";
  isProcessingMessage = false;
  const bytes = dataParser.stringBitsToBytes(msg);

  switch (bytes[0]) {
    case 23:
      module.exports.onMessageCallback(mpuParser.parseBytes(bytes));
      break;
  } // try {
  //     console.log('parsing message');
  //     console.dir(msg);
  //     const obj = JSON.parse(msg)
  //     module.exports.onMessageCallback(obj);
  // } catch (err) {
  //     console.error(err);
  // }

}

function testParse() {
  parseMessage("<000101110000000000101010110111010100000100011101000000001100010011111101111111100000000000000000>");
}

if (require.main === module) {
  testParse(); // process.argv.slice(2).forEach(parseMessage)
}