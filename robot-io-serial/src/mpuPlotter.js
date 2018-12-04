const plotter = require('./plotter');


module.exports = {
    plotMpu
}



function plotMpu(mpuData, timeStamp) {
    // console.log('plotting mpu');
    // console.dir(mpuData);
    plotData("x", mpuData.acc.x, timeStamp, "accelerometer")
    plotData("y", mpuData.acc.y, timeStamp, "accelerometer")
    plotData("z", mpuData.acc.z, timeStamp, "accelerometer")
    plotData("x", mpuData.gyro.x, timeStamp, "gyroscope")
    plotData("y", mpuData.gyro.y, timeStamp, "gyroscope")
    plotData("z", mpuData.gyro.z, timeStamp, "gyroscope")


}


function plotData(key, value, timeStamp, groupName) {
    const data = {
        key,
        value,
        timeStamp,
        groupName
    }
    plotter.appendDataSource(data)
}