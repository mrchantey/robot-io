

const SocketClient = require('./socketClient');
const initSystems = require('./systems');


window.addEventListener("load", _ => {

    SocketClient()
    initSystems()
    // socketClient.onDataCallback = (data, socket) => {
    //     console.log('data received..');
    //     el.innerHTML += "<br>" + JSON.stringify(data)
    //     console.dir(data);
    // }



})
