const Server = require('./server');
const J5 = require('./johnny5-interface');


//change hostname to "0.0.0.0" for cross-device access
const server = Server({ port: 8080, hostname: "localhost" })

const j5 = J5({ port: "COM7" })

j5.onDataCallback = server.sendData