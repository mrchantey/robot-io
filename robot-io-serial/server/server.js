const path = require('path');
const express = require('express');
const HTTP = require('http');
const IO = require('socket.io');

module.exports = createServer

function createServer({ port = 8080, hostname = "0.0.0.0" } = {}) {
    const app = express();
    const http = HTTP.Server(app)
    const io = IO(http)

    app.use(express.static('dist'))
    app.get('/', (req, res) => {
        res.sendFile(path.join(__dirname, "/../dist/index.html"))
    })
    http.listen(port, hostname, _ => console.log(`\nserver listening\nport:\t${port}\nhost:\t${hostname}\n`))


    let socketId = 0
    io.on('connection', socket => {
        const id = socketId++
        console.log(`socket ${id} connected..`);
        socket.on('disconnect', _ => console.log(`socket ${id} disconnected`))
        socket.on('data', data => {
            console.log(`data received:`)
            console.dir(data)
        })
        // socket.emit('data', { message: "welcome to the server" })
    })

    function sendMessage(obj) {
        console.log('sending message..');
        console.dir(obj);
        io.emit("data", obj)
    }

    return {
        sendMessage
    }
}
