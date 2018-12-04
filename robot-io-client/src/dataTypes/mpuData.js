const plotter = require('../plotter');


module.exports = {
    name: "mpuData",
    createInstance
}
const gyroOffset = -126


function createInstance() {

    const accChart = createAccelerometerChart()
    const gyroChart = createGyroChart()
    // const accTraces = await plotter.createTraces(accGroupEl, traceDatas)
    // console.dir(accChart);
    function onData(mpuData, timeStamp) {
        timeStamp /= 1000
        const newAccData = {
            x: [timeStamp, timeStamp, timeStamp],
            y: [mpuData.acc.x, mpuData.acc.y, mpuData.acc.z]
        }
        accChart.appendTraceDataBuffers(newAccData)
        const newGyroData = {
            x: [timeStamp, timeStamp, timeStamp],
            y: [mpuData.gyro.x + gyroOffset, mpuData.gyro.y + gyroOffset, mpuData.gyro.z + gyroOffset]
        }
        gyroChart.appendTraceDataBuffers(newGyroData)
    }

    const mpu = {
        name: 'mpuData',
        onData
    }

    return mpu
}


function createAccelerometerChart() {
    const groupData = {
        layout: {
            title: "Accelerometer",
            showlegend: true,
            xaxis: { title: "time (s)" },
            yaxis: { title: "units" },
            // plot_bgcolor: '#1E1E1E',
        }
    }
    const traceDatas = getVector3TraceDatas()
    const chart = plotter.createChart(groupData, traceDatas)
    return chart
}

function createGyroChart() {
    const groupData = {
        layout: {
            title: "Gyroscope",
            showlegend: true,
            xaxis: { title: "time (s)" },
            yaxis: { title: "units" },
            // plot_bgcolor: '#1E1E1E',
        }
    }
    const traceDatas = getVector3TraceDatas()
    const chart = plotter.createChart(groupData, traceDatas)
    return chart
}

function getVector3TraceDatas() {
    return [
        {
            name: "x",
            line: {
                color: 'rgb(255,0,0)'
            }
        },
        {
            name: "y",
            line: {
                color: 'rgb(0,255,0)'
            }
        },
        {
            name: "z",
            line: {
                color: 'rgb(0,0,255)'
            }
        }
    ]
}

// function plotMpu(mpuData, timeStamp) {
//     // console.log('plotting mpu');
//     // console.dir(mpuData);
//     plotData("x", mpuData.acc.x, timeStamp, "accelerometer")
//     plotData("y", mpuData.acc.y, timeStamp, "accelerometer")
//     plotData("z", mpuData.acc.z, timeStamp, "accelerometer")
//     plotData("x", mpuData.gyro.x, timeStamp, "gyroscope")
//     plotData("y", mpuData.gyro.y, timeStamp, "gyroscope")
//     plotData("z", mpuData.gyro.z, timeStamp, "gyroscope")


// }


// function plotData(key, value, timeStamp, groupName) {
//     const data = {
//         key,
//         value,
//         timeStamp,
//         groupName
//     }
//     plotter.appendDataSource(data)
// }