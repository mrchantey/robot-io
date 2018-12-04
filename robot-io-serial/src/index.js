const SocketClient = require('./socketClient');
const dataParser = require('./dataParser');

window.addEventListener('load', start)


function start() {
    const socketClient = SocketClient();
    socketClient.onDataCallback = dataParser.parseData
    // socketClient.receiveTestData();

    // messageListener.connect()

}