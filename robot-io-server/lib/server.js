"use strict";

module.exports = createServer;

function createServer() {
  let _ref = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : {},
      _ref$port = _ref.port,
      port = _ref$port === void 0 ? 8080 : _ref$port,
      _ref$hostname = _ref.hostname,
      hostname = _ref$hostname === void 0 ? "127.0.0.1" : _ref$hostname,
      _ref$open = _ref.open,
      open = _ref$open === void 0 ? false : _ref$open,
      _ref$dev = _ref.dev,
      dev = _ref$dev === void 0 ? false : _ref$dev;

  const path = require('path');

  const express = require('express');

  const app = express();

  const http = require('http').Server(app);

  const io = require('socket.io')(http);

  const opn = require('opn');

  const onDataListeners = []; // app.use(express.static('./build/static'))
  // app.use(express.static('./build'))
  //this should work both in npm_modules and the git repo

  const clientPath = '../../robot-io-client/build'; // const clientPath = dev ? '../build' : '../../robot-io-client/build'

  app.use(express.json());
  app.use(express.static(path.join(__dirname, clientPath)));
  app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, clientPath, "index.html"));
  });
  app.post('/', (req, res) => {
    console.log('POST RECEIVED');
    console.dir(req.body);
    server.sendData(req.body);
    res.send({
      message: 'message received'
    });
  });
  http.listen(port, hostname, _ => console.log(`\nserver listening\nhost:\t${hostname}\nport:\t${port}\n`));
  if (open) opn(`http://${hostname}:${port}`);
  let socketId = 0;
  io.on('connection', socket => {
    const id = socketId++;
    console.log(`socket ${id} connected..`);
    socket.on('disconnect', _ => console.log(`socket ${id} disconnected`));
    socket.on('data', data => {
      onDataListeners.forEach(l => l(data, socket, id));
    }); // socket.emit('data', { message: "welcome to the server" })
  });

  function sendData(obj) {
    console.log('sending data..');
    console.dir(obj);
    io.emit("data", obj);
  }

  const server = {
    sendData,
    onData: {
      addListener: lsn => onDataListeners.push(lsn)
    }
  };
  return server;
}

if (require.main === module) {
  const server = createServer();
}