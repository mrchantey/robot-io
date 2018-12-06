const argvIn = require('minimist')(process.argv.slice(2));
import Server from './server';

const argv = Object.assign({ port: 3000, hostname: "127.0.0.1" }, argvIn)

export default createServer

function createServer() {
    return Server(argv)
}