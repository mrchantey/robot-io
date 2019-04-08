const path = require('path');
const express = require('express');
const fs = require('fs');
const app = express();
const https = require('https').createServer({
    key: fs.readFileSync('./server/cert/server.key'),
    cert: fs.readFileSync('./server/cert/server.cert'),
}, app);

const request = require('request');

const io = require('socket.io')(https);
const open = require('opn');

app.use(express.static('dist'))
app.get('/', (req, res) => { res.sendFile(path.join(__dirname, "/../dist/index.html")) })

module.exports = createServer

function createServer({ port = 8080, hostname = "127.0.0.1", debug = true, robotIOServer = 'http://localhost:8080' } = {}) {
    const server = {
        onData: createEvent(),
        sendData
    }
    https.listen(port, hostname, _ => console.log(`\nserver listening\nhost:\t${hostname}\nport:\t${port}\n`))

    if (process.argv.includes('--open')) {
        const localHostname = hostname === '0.0.0.0' ? '127.0.0.1' : hostname
        open(`https://${localHostname}:${port}`)
    }
    let socketId = 0
    io.on('connection', socket => {
        const id = socketId++
        console.log(`socket ${id} connected..`);
        socket.on('disconnect', _ => console.log(`socket ${id} disconnected`))
        socket.on('data', data => server.onData.invoke(data))
    })

    function sendData(obj) {
        console.log('sending data..');
        console.dir(obj);
        io.emit("data", obj)
    }

    if (debug)
        server.onData.addListener(data => {
            // console.log(`data received from socket ${id}`);
            console.log(`data received:`);
            console.dir(data);
        })

    //TRY TO SEND TO ROBOT IO SERVER
    server.onData.addListener(data => {
        request.post(robotIOServer, {
            json: data
        }, (err, res, body) => {
            if (err)
                console.error(err)
            else
                console.log('request sent..');
        })
    })



    return server
}

if (require.main === module) {
    createServer()
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