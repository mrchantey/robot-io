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
        const initData = getInitData()
        ent.onData.invoke(initData)
        let valaX = 0
        let valaY = 0
        let valaZ = 0
        let valgX = 0
        let valgY = 0
        let valgZ = 0
        const beginMillis = Date.now()
        intervalID = setInterval(() => {
            valaX += Math.random() - 0.499999
            valaY += Math.random() - 0.499999
            valaZ += Math.random() - 0.499999
            valgX += Math.random() - 0.499999
            valgY += Math.random() - 0.499999
            valgZ += Math.random() - 0.499999
            const data = {
                timeStamp: (Date.now() - beginMillis) / 1000,
                data: [
                    { id: 1, value: valaX },
                    { id: 2, value: valaY },
                    { id: 3, value: valaZ },
                    { id: 4, value: valaZ },
                    { id: 5, value: valgX },
                    { id: 6, value: valgY },
                ]
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

function getInitData() {
    return {
        init:
            [{ type: 'chart', name: 'Accelerometer', id: 0 },
            { type: 'trace', name: 'x', id: 1, chartId: 0 },
            { type: 'trace', name: 'y', id: 2, chartId: 0 },
            { type: 'trace', name: 'z', id: 3, chartId: 0 },
            { type: 'chart', name: 'Gyroscope', id: 1 },
            { type: 'trace', name: 'x', id: 4, chartId: 1 },
            { type: 'trace', name: 'y', id: 5, chartId: 1 },
            { type: 'trace', name: 'z', id: 6, chartId: 1 }]
    }
    // return {
    //     init: [{ type: "chart", id: 0, name: "accelerometer", layout: { title: "accelerometer", showlegend: true, xaxis: { title: "time (s)" }, yaxis: { title: "units" }, plot_bgcolor: '#1E1E1E', } },
    //     { type: "trace", id: 1, chartId: 0, name: "x", settings: { mode: "markers"/*"lines" */ } }]
    // }
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