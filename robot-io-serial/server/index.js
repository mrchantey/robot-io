"use strict"
const SerialIO = require('./serialIO');
const Server = require('./server');

const args = {
    portName: "COM7",
    baudRate: 9600
}
for (let i = 2; i < process.argv.length; i += 2) {
    const key = process.argv[i].replace('-', '')
    args[key] = process.argv[i + 1]
}

const server = Server()

const serialIO = SerialIO(args.portName, args.baudRate)
serialIO.jsonParser.onMessageCallback = server.sendMessage

// console.log(__dirname);