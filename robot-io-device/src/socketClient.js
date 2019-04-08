

module.exports = createSocket

function createSocket(debug = true) {
    let socket
    try {
        socket = io()
        window.socket = socket
    }
    catch (err) {
        console.log("error caught:", err);
        return
    }
    socket.onData = createEvent()
    socket.on("data", data => socket.onData.invoke(data))
    socket.sendData = (data) => socket.emit("data", data)
    if (debug)
        socket.onData.addListener((data) => {
            console.log('data received..');
            console.dir(data);
        })
}

function createEvent() {
    const listeners = []
    return {
        addListener(listener) {
            listeners.push(listener)
        },
        invoke(data) {
            listeners.forEach(l => l(data))
        }
    }
}