// import CreateDataEntity from '../factories/dataEntityCreator';
import createChart from '../factories/entityCreators/chart';
import createTrace from '../factories/entityCreators/trace';

export default createDataEntityManager


function createDataEntityManager() {

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
        const chartDatas = data.init
            .filter(d => d.type === 'chart')
        charts = chartDatas.map(d => createChart(d))

        traces = data.init
            .filter(d => d.type === 'trace')
            .map(d => {
                const chart = charts.find(c => c.id === d.chartId)
                return createTrace(d, chart)
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
        charts.forEach(c => c.destroy())
        charts.length = 0
        // entities.forEach(e => e.resetData())
    }
    return manager
}