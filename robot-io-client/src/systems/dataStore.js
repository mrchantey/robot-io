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
        deleteData()
        onReset.invoke()
        const startMillis = Date.now()
        let i = 0;

        realtimeIntervalId = setInterval(_ => {
            const elapsedMillis = Date.now() - startMillis
            while (i < newData.length && newData[i].timeStamp < elapsedMillis) {
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
        setDataRealtime,
        stopDataRealtime,
        getData
    }
}
