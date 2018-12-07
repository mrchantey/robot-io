import Event from '../utility/event';

export default createDataStore

function createDataStore() {

    const data = []
    const onData = Event()
    const onReset = Event()

    function addData(newData) {
        data.push(newData)
        onData.invoke(newData)
    }

    function resetData() {
        deleteData()
    }

    function setData(newData = []) {
        deleteData()
        onReset.invoke()
        newData.forEach(nd => addData(nd))
        // newData.forEach(nd => data.push(nd))
    }

    function deleteData() {
        data.length = 0
        onReset.invoke()

    }

    let realtimeIntervalId

    function setDataRealtime(newData = [], onCompleteCallback) {
        resetData()
        const startMillis = Date.now()
        let i = 0;

        realtimeIntervalId = setInterval(_ => {
            const elapsedSeconds = (Date.now() - startMillis) / 1000
            while (i < newData.length && (newData[i].timeStamp === undefined || newData[i].timeStamp < elapsedSeconds)) {
                addData(newData[i])
                i++
            }
            if (i >= newData.length) {
                stopDataRealtime()
                onCompleteCallback()
            }
        }, 10)
    }

    function stopDataRealtime() {
        clearInterval(realtimeIntervalId)
    }

    function getData() {
        return data
    }

    return {
        addData,
        onData,
        onReset,
        setData,
        deleteData,
        resetData,
        setDataRealtime,
        stopDataRealtime,
        getData
    }
}
