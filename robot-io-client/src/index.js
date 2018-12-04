const SocketClient = require('./socketClient');
const DataParser = require('./dataParser');

window.addEventListener('load', start)


async function start() {
    const dataParser = DataParser(true)
    const socketClient = SocketClient()
    socketClient.onDataCallback = dataParser.parseData
    // socketClient.beginDataTest();
    socketClient.connect()
}