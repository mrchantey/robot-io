

module.exports = createSocketClient

function createSocketClient() {

    const socketClient = {
        socket: undefined,
        onDataCallback,
        sendData,
        beginDataTest
    }
    try {
        socketClient.socket = io()
        socketClient.socket.on("data", data => {
            socketClient.onDataCallback(data)
        })
    }
    catch (err) {
        console.log(err);
        return socketClient
    }

    function onDataCallback(data) {
        console.log('data received..');
        console.dir(data);
    }

    function sendData(data) {
        socketClient.socket.emit("data", data)
    }

    function beginDataTest() {
        const testData = {
            mpuData:
            {
                acc: { x: 5732, y: 1484, z: -15816 },
                gyro: { x: -334, y: -195, z: 1 },
                temp: 25
            },
            timeStamp: 661144
        }
        let lastMillis = Date.now()
        let startMillis = Date.now()
        setInterval(_ => {
            let millis = Date.now()
            let deltaMillis = millis - lastMillis
            lastMillis = millis
            // console.log(deltaMillis);
            testData.timeStamp = millis - startMillis
            // testData.timeStamp += 1000
            testData.mpuData.acc.x += getRandom()
            testData.mpuData.acc.y += getRandom()
            testData.mpuData.acc.z += getRandom()
            testData.mpuData.gyro.x += getRandom()
            testData.mpuData.gyro.y += getRandom()
            testData.mpuData.gyro.z += getRandom()
            // console.log('making data callback');
            // console.dir(testData);
            socketClient.onDataCallback(testData)
        }, 10);
    }
    return socketClient
}

function getRandom(max = 10000) {
    return Math.random() * max - max / 2
}