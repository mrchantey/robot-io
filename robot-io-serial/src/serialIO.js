
const SerialPort = require('serialport');
// const parser = require('./messageParser');
// const JsonParser = require('./jsonBufferParser');
// const readline = require('readline');

module.exports = createSerialIO

export default createSerialIO

function createSerialIO(argv) {
    const portName = argv.serialPort
    const baudRate = argv.baudRate
    const port = new SerialPort(portName, { baudRate }, err => { if (err) console.error(err) })

    const serialIO = {
        port,
        sendData,
        onBufferCallback: (buf) => console.log(`buffer received: ${buf.toString()}`),
    }

    port.on('open', data => {
        console.log(`Port opened..\nport name: ${portName}\nbaud rate: ${baudRate}\n`)
    })

    function sendData(data) {
        port.write(data, err => console.error(err))
    }

    port.on('data', buf => {
        serialIO.onBufferCallback(buf)
    })

    port.on('error', console.error);
    return serialIO
}

if (require.main === module) {

    // const rl = readline.createInterface({
    //     input: process.stdin,
    //     output: process.stdout,
    //     terminal: false
    // })
    // const portRX = createSerialPort("COM8", 9600)
    const serialIO = createSerialIO("COM7", 9600)
    // rl.on('line', msg => {
    //     if (msg === undefined)
    //         return
    //     console.log('message received', msg);
    //     serialIO.port.write(msg, console.error)
    // })
    // connect("COM8", 9600);
    // console.log(process.stdin);
}