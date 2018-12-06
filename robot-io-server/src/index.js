const argvIn = require('minimist')(process.argv.slice(2));
import Server from './server';

const argv = Object.assign({ port: 3000, hostname: "127.0.0.1" }, argvIn)

export default createRobotIO
module.exports = createRobotIO

function createRobotIO() {

    const server = Server(argv)
    const robotIO = {
        server,
        addMiddleware
    }

    function addMiddleware(middleware) {
        server.onData.addListener(middleware.sendData)
        middleware.onData.addListener(server.sendData)
    }

    return robotIO
}