const SerialPort = require('serialport');
// const parser = require('./messageParser');
const JsonParser = require('./jsonBufferParser');
const readline = require('readline');

module.exports = createSerialIO

function createSerialIO(portName, baudRate) {

    const jsonParser = JsonParser()

    const port = new SerialPort(portName, { baudRate }, err => { if (err) console.error(err) })

    port.on('open', data => {
        console.log(`Port opened..\nport name: ${portName}\nbaud rate: ${baudRate}\n`)
        // port.write('1', console.error)
    })

    port.on('data', buf => {
        // const bufStr = buf.toString()
        // console.log(`buffer received: ${bufStr}`);
        jsonParser.parseBuffer(buf)
    })

    port.on('error', console.error);

    const serialIO = {
        port,
        jsonParser
    }
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