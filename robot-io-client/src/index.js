const SocketClient = require('./socketClient');
const DataParser = require('./dataParser');

module.exports = createRobotIOClient

function createRobotIOClient() {
    const dataParser = DataParser(true)
    const socketClient = SocketClient()
    socketClient.onDataCallback = dataParser.parseData
    // socketClient.beginDataTest();
    return {
        dataParser,
        socketClient
    }
}
