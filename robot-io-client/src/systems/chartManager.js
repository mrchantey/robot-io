// import CreateDataEntity from '../factories/dataEntityCreator';
import createChart from '../factories/entityCreators/chart';
import createTrace from '../factories/entityCreators/trace';

export default createChartManager


function createChartManager() {

    let charts = []
    let traces = []


    const manager = {
        charts,
        addData,
        resetData
    }


    function addData(data) {
        parseInit(data)
        parseData(data)
    }

    function parseInit(data) {
        if (data.init === undefined)
            return
        // window.systems.dataStore.resetData()

        data.init
            .filter(d => d.type === 'chart')
            .forEach(d => replaceOrPushEntity(createChart(d), charts))

        data.init
            .filter(d => d.type === 'trace')
            .forEach(d => {
                const chart = charts.find(c => c.id === d.chartId)
                replaceOrPushEntity(createTrace(d, chart), traces)
            })

    }
    function parseData(data) {
        if (data.data === undefined)
            return
        data.data.forEach(d => {
            const trace = traces.find(t => t.id === d.id)
            if (trace === undefined)
                //TODO IF DOESNT EXIST, CREATE IT
                console.log(`trace not found matching ${d.name}`);
            else {

                trace.appendDataBuffer(d.value, data.timeStamp)
            }
        })
    }

    function resetData() {
        // traces.forEach(t => t.destroy())
        traces.length = 0
        charts.forEach(c => c.destroy())
        charts.length = 0
        // entities.forEach(e => e.resetData())
    }
    return manager
}
function replaceOrPushEntity(entity, arr) {
    const matchingEnt = arr.find(ent => ent.id === entity.id)
    if (matchingEnt === undefined) {
        arr.push(entity)
    } else {
        const index = arr.indexOf(matchingEnt)
        matchingEnt.destroy()
        arr[index] = entity
    }
}