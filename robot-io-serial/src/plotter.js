const Plotly = require('plotly.js-dist');

module.exports = {
    // registerDataSource,
    appendDataSource
}

const dataGroups = []

function appendDataSource(_source) {
    const source = assertSource(_source)
    if (source.key === undefined || source.value === undefined) {
        console.warn("source missing data", source);
        return
    }

    const group = getGroup(source)

    const trace = getTrace(group, source)

    appendTrace(group, source, trace)

    // console.log(index)
}



function assertSource(_source) {
    const source = {
        groupName: "group 1",
        type: "number",
        // key: "trace1",
    }
    source.layout = {
        // plot_bgcolor: '#1E1E1E',
        showlegend: true,
        xaxis: { title: "time (ms)" },
        yaxis: { title: "units" },
    }
    Object.assign(source, _source)
    source.layout.title = source.groupName
    return source
}

function getGroup(source) {
    const group = dataGroups.find(g => g.id === source.groupName) || createGroup(source)
    return group
}

function createGroup(source) {
    const el = document.createElement("div")
    document.body.appendChild(el)
    el.id = source.groupName
    Plotly.newPlot(el, [], source.layout)
    dataGroups.push(el)
    return el
}

function getTrace(el, source) {
    // console.log('getting trace');
    let trace = el.data.find(d => d.name === source.key)
    // console.log(el.data);
    if (!source.key || !trace)
        trace = createTrace(el, source)
    // console.log(trace);
    trace.groupIndex = el.data.indexOf(trace)
    return trace
}

function createTrace(el, source) {
    // console.log('creating trace');
    const trace = {
        name: source.key,
        // type: 'scatter',
        x: [],
        y: [],
        // x: [1, 2, 3, 4],
        // y: [Math.random(), Math.random(), Math.random(), Math.random()],
        mode: 'lines',
        line: {
            // color: 'rgb(219, 64, 82)',
            width: 3
        }
    };
    Object.assign(trace, source.trace)
    source.trace = trace
    if (source.key === undefined) {
        const dataIndex = el.data.length
        source.trace.name = `data ${dataIndex}`
        source.key = source.trace.name
    }
    Plotly.addTraces(el, source.trace)
    return trace
}

function appendTrace(group, source, trace) {
    const count = trace.x.length
    const x = source.timeStamp === undefined ? trace.x.length + 1 : source.timeStamp
    const y = source.value || 0
    // console.log(source.timeStamp);
    // console.log(x);
    Plotly.extendTraces(group.id, { x: [[x]], y: [[y]] }, [trace.groupIndex])
    // const maxPointsDisplayed = 500
    const maxPointsDisplayed = 100
    // console.log(count);
    // console.log(group.layout.xaxis);
    if (count > maxPointsDisplayed) {
        const min = trace.x[count - maxPointsDisplayed]
        const max = trace.x[count]
        // console.log(`maxed out\tmin:${min}\tmax:${max}`);
        const layout = {}
        Object.assign(layout, group.layout)
        // Object.assign(layout.xaxis, { range: [count - maxPointsDisplayed, count] })
        Object.assign(layout.xaxis, { autorange: false, range: [min, max] })
        // console.log(layout.xaxis);
        Plotly.relayout(group, layout)
    }
}