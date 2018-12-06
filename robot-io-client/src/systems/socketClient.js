import Event from '../utility/event';
import io from 'socket.io-client';
// module.exports = createSocketClient

export default createSocketClient



function createSocketClient(debug = false) {

    const socketClient = {
        socket: undefined,
        onData: Event(),
        sendData,
    }
    try {

        //untested!
        // if (window.io !== undefined) {
        console.log('connecting to socket server...');
        socketClient.socket = io()
        socketClient.socket.on('connect', _ => {
            console.log('socket connected!');
        })
        socketClient.socket.on("data", data => {
            socketClient.onData.invoke(data)
        })
    }
    catch (err) {
        console.log(err);
        return socketClient
    }
    if (debug) {
        socketClient.onData.addListener(data => {
            console.log('data received..');
            console.dir(data);
        })
    }

    function sendData(data) {
        socketClient.socket.emit("data", data)
    }


    return socketClient
}

