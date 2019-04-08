const SensorUtil = require('./sensorUtility');


module.exports = createAbsOrientationSensor
function createAbsOrientationSensor() {

    let sensor
    try {
        sensor = new AbsoluteOrientationSensor({ frequency: 60 })
    } catch{
        SensorUtil.sendMessage({ messageType: 'error', message: 'browser not supported, please use chrome' })
        return SensorUtil.createDummySensor()
    }

    const chartId = SensorUtil.GetUUID()
    const qxId = SensorUtil.GetUUID()
    const qyId = SensorUtil.GetUUID()
    const qzId = SensorUtil.GetUUID()
    const qwId = SensorUtil.GetUUID()
    const aaxId = SensorUtil.GetUUID()
    const aayId = SensorUtil.GetUUID()
    const aazId = SensorUtil.GetUUID()
    const aathetaId = SensorUtil.GetUUID()

    function reset() {
        const initData = {
            init: [
                { type: "chart", name: "Absolute Orientation Sensor", id: chartId },
                { type: "trace", name: "qx", id: qxId, chartId },
                { type: "trace", name: "qy", id: qyId, chartId },
                { type: "trace", name: "qz", id: qzId, chartId },
                { type: "trace", name: "qw", id: qwId, chartId },
                { type: "trace", name: "aaxId", id: aaxId, chartId },
                { type: "trace", name: "aayId", id: aayId, chartId },
                { type: "trace", name: "aazId", id: aazId, chartId },
                { type: "trace", name: "aathetaId", id: aathetaId, chartId },
            ]
        }
        SensorUtil.sendMessage(initData)
    }


    sensor.onreading = (event) => {
        const q = sensor.quaternion
        const aa = quaternion2AngleAxis(q[0], q[1], q[2], q[3])
        const message = {
            data: [
                { id: qxId, value: q[0] },
                { id: qyId, value: q[1] },
                { id: qzId, value: q[2] },
                { id: qwId, value: q[3] },
                { id: aaxId, value: aa.x },
                { id: aayId, value: aa.y },
                { id: aazId, value: aa.z },
                { id: aathetaId, value: aa.theta },
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

function quaternion2AngleAxis(x, y, z, w) {
    const w2 = w * w
    const aa = {
        theta: 2 * Math.acos(w),
        x: x / Math.sqrt(1 - w2),
        y: y / Math.sqrt(1 - w2),
        z: z / Math.sqrt(1 - w2),
    }
    aa.mag = Math.sqrt(aa.x * aa.x + aa.y * aa.y + aa.z * aa.z)
    return aa
}

// sensor.onreading = (event) => {
//     const q = sensor.quaternion
//     const aa = quaternion2AngleAxis(q[0], q[1], q[2], q[3])
//     const message = {
//         messageType: 'reading',
//         sensorType: 'AbsoluteOrientationSensor',
//         quaternion: q,
//         axisAngle: aa
//     }
//     SensorUtil.sendMessage({ messageType: 'reading', message })
// }