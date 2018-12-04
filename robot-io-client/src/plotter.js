const Plotly = require('plotly.js-dist');

module.exports = {
    createChart,
}
function createChart(groupData, traceDatas, autoUpdate = true, updateInterval = 30) {

    const groupEl = createGroup(groupData)

    // console.dir(groupEl);
    const traceDataBuffers = {
        x: traceDatas.map(d => []),
        y: traceDatas.map(d => []),
        indicies: traceDatas.map((t, i) => i)
    }

    function appendTraceDataBuffers(newTraceDatas) {
        // console.dir(traceDataBuffers);
        newTraceDatas.x.forEach((xData, i) => traceDataBuffers.x[i].push(xData))
        newTraceDatas.y.forEach((yData, i) => traceDataBuffers.y[i].push(yData))
        // console.dir(traceDataBuffers);
    }

    function update() {
        appendTraces(groupEl, traceDataBuffers)
        traceDataBuffers.x.forEach(arr => arr.length = 0)
        traceDataBuffers.y.forEach(arr => arr.length = 0)
    }

    let traces;
    // const traces = await createTraces(groupEl, traceDatas)
    createTraces(groupEl, traceDatas)
        .then(_traces => {
            traces = _traces
            if (autoUpdate)
                setInterval(update, updateInterval);
        })
        .catch(console.error)

    const chart = {
        groupEl,
        //traces will initially be undefined
        traces,
        appendTraceDataBuffers,
        update
    }
    return chart
}
// async function createChartAsync(groupData, traceDatas, autoUpdate = true) {

//     const groupEl = createGroup(groupData)
//     const traces = await createTraces(groupEl, traceDatas)

//     const traceDataBuffers = {
//         x: groupEl.data.map(d => []),
//         y: groupEl.data.map(d => []),
//         indicies: groupEl.data.map((t, i) => i)
//     }

//     function appendTraceDataBuffers(newTraceDatas) {
//         newTraceDatas.x.forEach((xData, i) => traceDataBuffers.x[i].push(xData))
//         newTraceDatas.y.forEach((yData, i) => traceDataBuffers.y[i].push(yData))
//         // console.dir(traceDataBuffers);
//     }

//     function update() {
//         appendTraces(groupEl, traceDataBuffers)
//         traceDataBuffers.x.forEach(arr => arr.length = 0)
//         traceDataBuffers.y.forEach(arr => arr.length = 0)
//     }
//     if (autoUpdate)
//         setInterval(update, 30);


//     const chart = {
//         groupEl,
//         traces,
//         appendTraceDataBuffers,
//         update
//     }
//     return chart
// }

function createGroup(groupData) {
    const el = document.createElement("div")
    document.body.appendChild(el)
    Plotly.newPlot(el, [], groupData.layout)
    // dataGroups.push(el)
    return el
}

async function createTraces(groupEl, _traceDatas) {
    const traceDatas = _traceDatas.map(d => validateTraceData(groupEl, d))
    await Plotly.addTraces(groupEl, traceDatas)
    const traces = groupEl.data.reduce((acc, d) => {
        d.groupIndex = groupEl.data.indexOf(d)
        acc[d.name] = d
        return acc
    }, {})
    return traces
}

function validateTraceData(groupEl, _traceData) {
    const traceData = {
        name: `data ${groupEl.data.length}`,
        type: 'scattergl',
        // type: 'line',
        mode: 'lines',
        x: [],
        y: [],
        line: {
            // color: 'rgb(219, 64, 82)',
            width: 3
        },
    }
    Object.assign(traceData, _traceData)
    return traceData
}

function appendTraces(groupEl, newTraceDatas) {
    Plotly.extendTraces(groupEl, { x: newTraceDatas.x, y: newTraceDatas.y }, newTraceDatas.indicies)
    const count = groupEl.data[0].x.length - 1
    const maxPointsDisplayed = 100
    if (count > maxPointsDisplayed) {
        const min = groupEl.data[0].x[count - maxPointsDisplayed]
        const max = groupEl.data[0].x[count]
        const layout = {}
        Object.assign(layout, groupEl.layout)
        Object.assign(layout.xaxis, { autorange: false, range: [min, max] })
        Plotly.relayout(groupEl, layout)
    }
}