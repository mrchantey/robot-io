import Event from '../utility/event';


export default createDataInputTest



function createDataInputTest() {
    const onData = Event()
    const onReset = Event()
    const ent = {
        begin,
        end,
        onData,
        onReset
    }
    let intervalID;

    function begin() {
        window.systems.dataStore.resetData()
        const initData = {
            init: [{
                type: "chart",
                id: 0,
                name: "accelerometer"
                // layout: {
                //     title: "accelerometer",
                //     showlegend: true,
                //     xaxis: { title: "time (s)" },
                //     yaxis: { title: "units" }
                // plot_bgcolor: '#1E1E1E',
                // }
            },
            {
                type: "trace",
                id: 1,
                chartId: 0,
                name: "x",
                settings: {
                    mode: "markers"
                    // mode: "lines"
                }
            }
            ]
        }
        ent.onData.invoke(initData)
        let value = 0
        const beginMillis = Date.now()
        intervalID = setInterval(() => {
            value += Math.random() - 0.499999
            const data = {
                timeStamp: (Date.now() - beginMillis) / 1000,
                data: [{
                    id: 1,
                    value
                }]
            }
            ent.onData.invoke(data)
        }, 100);

    }

    function end() {
        clearInterval(intervalID)
        onReset.invoke()
    }

    return ent


}


// function begin() {
//     ent.onReset.invoke()
//     // let lastMillis = Date.now()
//     let startMillis = Date.now()

//     let accX = 0
//     let accY = 0
//     let accZ = 0
//     let gyroX = 0
//     let gyroY = 0
//     let gyroZ = 0

//     intervalID = setInterval(_ => {
//         let millis = Date.now()

//         accX += getRandom()
//         accY += getRandom()
//         accZ += getRandom()
//         gyroX += getRandom()
//         gyroY += getRandom()
//         gyroZ += getRandom()

//         const testData = {
//             mpu:
//             {
//                 acc: { x: accX, y: accY, z: accZ },
//                 gyro: { x: gyroX, y: gyroY, z: gyroZ },
//                 temp: 25
//             },
//             timeStamp: millis - startMillis
//         }
//         // let deltaMillis = millis - lastMillis
//         // lastMillis = millis
//         // testData.timeStamp += 1000
//         // console.log('making data callback');
//         // console.dir(testData);
//         ent.onData.invoke(testData)
//     }, 10);
// }