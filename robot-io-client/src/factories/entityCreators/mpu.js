import * as vec3 from './vec3';

export let name = "MPU 6050"
export let shortName = "mpu"

export function create() {
    const accelerometer = vec3.create({ name: "Accelerometer" })
    const gyroscope = vec3.create({ name: "Gyroscope" })
    function addData(mpuData, timeStamp) {
        // console.log(`data received at ${timeStamp}`);
        accelerometer.addData(mpuData.acc, timeStamp)
        gyroscope.addData(mpuData.gyro, timeStamp)
    }
    function resetData() {
        accelerometer.resetData()
        gyroscope.resetData()
    }

    return {
        name,
        shortName,
        accelerometer,
        gyroscope,
        addData,
        resetData
    }
}