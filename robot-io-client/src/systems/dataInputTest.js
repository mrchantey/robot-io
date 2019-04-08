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

        const accInit = getAccInit()
        const gyroInit = getGyroInit()
        ent.onData.invoke(gyroInit)
        ent.onData.invoke(accInit)

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
                    { id: 5, value: valgX },
                    { id: 6, value: valgY },
                    { id: 4, value: valgZ },
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

function getAccInit() {
    return {
        init: [
            { type: 'chart', name: 'Accelerometer', id: 0 },
            { type: 'trace', name: 'x', id: 1, chartId: 0, settings: { mode: 'lines+markers' } },
            { type: 'trace', name: 'y', id: 2, chartId: 0 },
            { type: 'trace', name: 'z', id: 3, chartId: 0 },]
    }
}

function getGyroInit() {
    return {
        init: [
            { type: 'chart', name: 'Gyroscope', id: 1 },
            { type: 'trace', name: 'x', id: 4, chartId: 1, settings: { mode: 'lines+markers' } },
            { type: 'trace', name: 'y', id: 5, chartId: 1 },
            { type: 'trace', name: 'z', id: 6, chartId: 1 }]
    }
}

