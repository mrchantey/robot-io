const Server = require('./server');

const server = Server({ port: 8081, hostname: "0.0.0.0" })

// server.onData.addListener() = (data, socket, id) => {
//     console.log(`data received from socket ${id}`);
//     console.dir(data);
// }

// let count = 0
// setInterval(() => {
//     server.sendData({ message: `important data ${count++}` })
// }, 1000);