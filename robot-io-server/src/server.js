
module.exports = createServer

function createServer({ port = 8080, hostname = "127.0.0.1", open = false } = {}) {
    const path = require('path');
    const express = require('express');
    const app = express();
    const http = require('http').Server(app);
    const io = require('socket.io')(http);
    const opn = require('opn');

    // app.use(express.static('./build/static'))
    // app.use(express.static('./build'))
    app.use(express.static(path.join(__dirname, '../build')))
    app.get('/', (req, res) => {
        res.sendFile(path.join(__dirname, '../build', "index.html"))
    })

    http.listen(port, hostname, _ => console.log(`\nserver listening\nhost:\t${hostname}\nport:\t${port}\n`))
    if (open) opn(`http://${hostname}:${port}`)

    let socketId = 0
    io.on('connection', socket => {
        const id = socketId++
        console.log(`socket ${id} connected..`);
        socket.on('disconnect', _ => console.log(`socket ${id} disconnected`))
        socket.on('data', data => {
            module.exports.onDataCallback(data, socket, id)
        })

        // socket.emit('data', { message: "welcome to the server" })
    })

    function sendData(obj) {
        console.log('sending data..');
        console.dir(obj);
        io.emit("data", obj)
    }

    function onDataCallback(data, socket, id) {
        console.log(`data received from socket ${id}`);
        console.dir(data);
    }

    const server = {
        sendData,
        onDataCallback
    }

    return server
}


if (require.main === module) {
    const server = createServer()
}