import JsonBufferParser from './jsonBufferParser';
import SerialIO from './serialIO';

const argvIn = require('minimist')(process.argv.slice(2));
const argv = { serialPort: "COM7", baudRate: 9600 }
Object.assign(argv, argvIn)

export default createRobotSerial
module.exports = createRobotSerial

function createRobotSerial() {
    const serialIO = SerialIO(argv)
    const jsonBufferParser = JsonBufferParser(argv)
    serialIO.onBufferCallback = jsonBufferParser.parseBuffer
    jsonBufferParser.onDataCallback = data => onDataListeners.forEach(l => l(data))

    const onDataListeners = []
    const onData = {
        addListener: listener => onDataListeners.push(listener),
    }

    const robotSerial = {
        serialIO,
        jsonBufferParser,
        onData,
        sendData: data => serialIO.sendData(JSON.stringify(data))
    }

    if (argv.debug === true) {
        robotSerial.onData.addListener(data => {
            console.log('data received');
            console.dir(data);
        });
    }

    return robotSerial
}

