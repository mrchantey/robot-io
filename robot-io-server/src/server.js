
module.exports = createServer

function createServer({ port = 8080, hostname = "127.0.0.1", open = false, dev = false } = {}) {
    const path = require('path');
    const express = require('express');
    const app = express();
    const http = require('http').Server(app);
    const io = require('socket.io')(http);
    const opn = require('opn');

    const onDataListeners = []

    // app.use(express.static('./build/static'))
    // app.use(express.static('./build'))

    const clientPath = dev ? '../build' : '../node_modules/robot-io-client/build'

    app.use(express.static(path.join(__dirname, clientPath)))
    app.get('/', (req, res) => {
        res.sendFile(path.join(__dirname, clientPath, "index.html"))
    })

    http.listen(port, hostname, _ => console.log(`\nserver listening\nhost:\t${hostname}\nport:\t${port}\n`))
    if (open) opn(`http://${hostname}:${port}`)

    let socketId = 0
    io.on('connection', socket => {
        const id = socketId++
        console.log(`socket ${id} connected..`);
        socket.on('disconnect', _ => console.log(`socket ${id} disconnected`))
        socket.on('data', data => {
            onDataListeners.forEach(l => l(data, socket, id))
        })

        // socket.emit('data', { message: "welcome to the server" })
    })

    function sendData(obj) {
        console.log('sending data..');
        console.dir(obj);
        io.emit("data", obj)
    }

    const server = {
        sendData,
        onData: {
            addListener: lsn => onDataListeners.push(lsn)
        }
    }

    return server
}


if (require.main === module) {
    const server = createServer()
}