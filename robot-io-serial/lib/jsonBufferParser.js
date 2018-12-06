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

function createJsonBufferParser() {
  // let incompleteMessage = ""
  // let incompleteMessageDepth = 0;
  let jsonStr = "";
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
        jsonBufferInProgress = true;
      } else if (chr === '>' && jsonStr != '') {
        jsonBufferInProgress = false;
        onMessageComplete(jsonStr);
        jsonStr = '';
      } else if (jsonBufferInProgress === true) {
        jsonStr += chr;
      }
    }
  }

  function onMessageComplete(msg) {
    try {
      // console.log('parsing message');
      msg = msg.replace('\r\n', ''); // console.dir(msg);

      const obj = JSON.parse(msg); // console.dir(obj);

      bufParser.onDataCallback(obj);
    } catch (err) {
      console.error(err);
    }
  }

  return bufParser;
}