const SensorUtil = require('./sensorUtility');

Math.TWO_PI = Math.PI * 2

module.exports = createGyroSensor

function createGyroSensor() {
    let sensor
    try {
        sensor = new Gyroscope({ frequency: 60 })
    } catch{
        SensorUtil.sendMessage({ messageType: 'error', message: 'browser not supported, please use chrome' })
        return SensorUtil.createDummySensor()
    }

    const chartId = SensorUtil.GetUUID()
    const gxId = SensorUtil.GetUUID()
    const gyId = SensorUtil.GetUUID()
    const gzId = SensorUtil.GetUUID()

    function reset() {
        const initData = {
            init: [
                { type: "chart", name: "Gyroscope Sensor", id: chartId },
                { type: "trace", name: "gx", id: gxId, chartId },
                { type: "trace", name: "gy", id: gyId, chartId },
                { type: "trace", name: "gz", id: gzId, chartId },
            ]
        }
        SensorUtil.sendMessage(initData)
    }

    //radians per second
    sensor.onreading = (event) => {
        const message = {
            data: [
                { id: gxId, value: sensor.x },
                { id: gyId, value: sensor.y },
                { id: gzId, value: sensor.z },
            ]
        }
        SensorUtil.sendMessage(message)
    }

    sensor.onerror = (errEvent) => SensorUtil.sendMessage({ messageType: 'error', message: errEvent.error.name })

    const sensorWrapper = {
        start() { reset(); sensor.start() },
        stop() { sensor.stop() },
        reset
    }

    return sensorWrapper
}

    // sensor.onreading = (event) => {
    //     //data is in Hz
    //     const message = {
    //         sensorType: 'Gyroscope',
    //         radiansPerSecond: {
    //             x: sensor.x,
    //             y: sensor.y,
    //             z: sensor.z,
    //         },
    //         hertz: {
    //             x: sensor.x / Math.TWO_PI,
    //             y: sensor.y / Math.TWO_PI,
    //             z: sensor.z / Math.TWO_PI,
    //         }
    //     }
    //     SensorUtil.sendMessage({ messageType: 'reading', message })
    // }