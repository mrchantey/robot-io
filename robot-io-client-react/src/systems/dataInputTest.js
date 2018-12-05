import Event from '../utility/event';


export default createDataInputTest



function createDataInputTest() {
    const ent = {
        begin,
        end,
        onData: Event(),
        onReset: Event()
    }

    let intervalID;
    function begin() {
        ent.onReset.invoke()
        // let lastMillis = Date.now()
        let startMillis = Date.now()

        let accX = 0
        let accY = 0
        let accZ = 0
        let gyroX = 0
        let gyroY = 0
        let gyroZ = 0

        intervalID = setInterval(_ => {
            let millis = Date.now()

            accX += getRandom()
            accY += getRandom()
            accZ += getRandom()
            gyroX += getRandom()
            gyroY += getRandom()
            gyroZ += getRandom()

            const testData = {
                mpu:
                {
                    acc: { x: accX, y: accY, z: accZ },
                    gyro: { x: gyroX, y: gyroY, z: gyroZ },
                    temp: 25
                },
                timeStamp: millis - startMillis
            }
            // let deltaMillis = millis - lastMillis
            // lastMillis = millis
            // testData.timeStamp += 1000
            // console.log('making data callback');
            // console.dir(testData);
            ent.onData.invoke(testData)
        }, 10);
    }

    function end() {
        clearInterval(intervalID)
    }

    function getRandom(max = 10000) {
        return Math.random() * max - max / 2
    }

    return ent


}

