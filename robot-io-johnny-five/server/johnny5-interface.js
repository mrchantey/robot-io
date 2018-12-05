const five = require('johnny-five');

module.exports = createJ5Interface

function createJ5Interface({ port = "COM1" } = {}) {
    const board = new five.Board({
        port
    })
    board.on("error", console.error)

    function onDataCallback(data) {
        console.log('data emitted');
        console.dir(data);
    }

    const j5 = {
        onDataCallback
    }

    board.on("ready", _ => {
        const imu = new five.IMU({
            controller: "MPU6050"
        });

        const acc = imu.accelerometer
        const gyro = imu.gyro

        const startMillis = Date.now()
        let lastMillis = Date.now()
        imu.on("data", _ => {
            const millis = Date.now()
            const deltaMillis = millis - lastMillis
            let timeStamp = millis - startMillis
            if (deltaMillis > 100) {
                const socketData = {
                    mpuData: {
                        acc: { x: acc.x, y: acc.y, z: acc.z },
                        gyro: { x: gyro.x, y: gyro.y, z: gyro.z }
                    },
                    timeStamp
                }
                j5.onDataCallback(socketData)
                lastMillis = millis
            }
        })
    })
    return j5
}


    // Can also be written as: 
    // const sensor = new five.Sensor.Digital(7);
    // sensor.on('data', console.log)
    // board.pinMode(13, five.Pin.OUTPUT)
    // board.pinMode(7, five.Pin.INPUT)

    // board.digitalRead(7, console.log)


    // let isOn = false
    // setInterval(() => {
    // isOn = !isOn
    // board.digitalWrite(13, isOn ? 1 : 0)
    // board.digitalRead(13, console.log);
    // }, 1000);

