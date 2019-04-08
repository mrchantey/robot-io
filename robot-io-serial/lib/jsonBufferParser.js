"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.default = void 0;

require("core-js/modules/es6.regexp.replace");

require("core-js/modules/es6.regexp.to-string");

var _default = createJsonBufferParser;
exports.default = _default;
module.exports = createJsonBufferParser;

function createJsonBufferParser(argv) {
  // let incompleteMessage = ""
  // let incompleteMessageDepth = 0;
  let jsonStr = '';
  let jsonBufferInProgress = false;
  const bufParser = {
    parseBuffer,
    onDataCallback: data => {
      console.log(`message received:`);
      console.dir(msg);
    }
  };

  function parseBuffer(buf) {
    const bufStr = buf.toString();

    for (let i = 0; i < bufStr.length; i++) {
      const chr = bufStr.charAt(i);

      if (chr === '<') {
        jsonStr = '';
        jsonBufferInProgress = true;
      } else if (chr === '>' && jsonBufferInProgress === true) {
        jsonBufferInProgress = false;
        onMessageComplete(jsonStr);
        jsonStr = '';
      } else if (jsonBufferInProgress === true) {
        jsonStr += chr;
      }
    }
  }

  function onMessageComplete(msg) {
    msg = msg.replace('\r\n', '');

    try {
      const obj = JSON.parse(msg);
      bufParser.onDataCallback(obj);
    } catch (err) {
      if (argv.debug === true) {
        console.log(`bad json message: ${msg}`);
        console.error(err);
      }
    }
  }

  return bufParser;
}