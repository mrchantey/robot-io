import JsonBufferParser from './jsonBufferParser';
import SerialIO from './serialIO';

export default createRobotSerial
module.exports = createRobotSerial

function createRobotSerial() {
    const serialIO = SerialIO()
    const jsonBufferParser = JsonBufferParser()
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
    return robotSerial
}

