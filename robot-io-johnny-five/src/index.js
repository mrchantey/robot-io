const Client = require('robot-io-client');

window.addEventListener('load', start)


async function start() {
    const client = Client()
    client.socketClient.beginDataTest()

}