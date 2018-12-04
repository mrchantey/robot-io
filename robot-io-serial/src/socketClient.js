

module.exports = createSocketClient

function createSocketClient() {
    const socketClient = {
        socket: undefined,
        onDataCallback,
        receiveTestData
    }

    try {
        socketClient.socket = io()
        console.log('socket connecting..');
        socketClient.socket.on("connect", _ => console.log('socket connected!'))
        socketClient.socket.on("data", data => {
            socketClient.onDataCallback(data)
            // socket.emit("data", { message: "thank you, data received" })
        })
    }
    catch (err) {
        console.log(err);
        return
    }

    function onDataCallback(data) {
        console.log('data received..');
        console.dir(data);
    }

    function receiveTestData() {
        const testData = {
            mpuData:
            {
                acc: { x: 5732, y: 1484, z: -15816 },
                gyro: { x: -334, y: -195, z: 1 },
                temp: 25
            },
            timeStamp: 661144
        }
        setInterval(_ => {
            testData.timeStamp += 1000
            testData.mpuData.acc.x += getRandom()
            testData.mpuData.acc.y += getRandom()
            testData.mpuData.acc.z += getRandom()
            testData.mpuData.gyro.x += getRandom()
            testData.mpuData.gyro.y += getRandom()
            testData.mpuData.gyro.z += getRandom()
            // console.log('making data callback');
            // console.dir(testData);
            module.exports.onDataCallback(testData)
        }, 1000);
    }
    return socketClient
}



function getRandom(max = 10000) {
    return Math.random() * max - max / 2
}