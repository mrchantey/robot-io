const Client = require('../src/index');

window.addEventListener('load', start)

function start() {
    const client = Client()
    client.socketClient.beginDataTest()
}


// console.log('hello world');