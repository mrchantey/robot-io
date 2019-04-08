
const CreateGyroSensor = require('./gyro');
const CreateAbsOrientationSensor = require('./absOrientationSensor');

module.exports = initializeSensors


function initializeSensors() {

    // await queryPermissions()

    const sensors = {
        absOrientation: CreateAbsOrientationSensor(),
        gyro: CreateGyroSensor()
    }

    function forEachSensor(func) {
        Object.keys(sensors).forEach(k => func(sensors[k]))
    }

    console.dir(sensors);

    const sensorSystem = {
        start() { forEachSensor(s => s.start()) },
        stop() { forEachSensor(s => s.stop()) },
        reset() { forEachSensor(s => s.reset()) },
    }

    return sensorSystem
}




// async function queryPermissions() {
    // const acc = await navigator.permissions.query({ name: 'accelerometer' })
    // update(`accelerometer permission: ${acc.state}`)
    // const gyro = await navigator.permissions.query({ name: 'gyroscope' })
    // update(`gyroscope permission: ${gyro.state}`)
    // if (navigator.permissions) {
    //     // https://w3c.github.io/orientation-sensor/#model
    //     Promise.all([navigator.permissions.query({ name: "accelerometer" }),
    //                  navigator.permissions.query({ name: "magnetometer" }),
    //                  navigator.permissions.query({ name: "gyroscope" })])
    //            .then(results => {
    //                 if (results.every(result => result.state === "granted")) {
    //                     initSensor();
    //                 } else {
    //                     console.log("Permission to use sensor was denied.");
    //                 }
    //            }).catch(err => {
    //                 console.log("Integration with Permissions API is not enabled, still try to start app.");
    //                 initSensor();
    //            });
    // } else {
    //     console.log("No Permissions API, still try to start app.");
    //     initSensor();
    // }

// }