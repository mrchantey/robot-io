import circleAssign from 'circle-assign';
const Plotly = require('plotly.js-dist');


// const idCounte

export default function createChart(_chart) {

    const chart = circleAssign({
        layout: {
            title: _chart.name,
            showlegend: true,
            xaxis: { title: "time (s)" },
            yaxis: { title: "units" },
            // plot_bgcolor: '#1E1E1E',
        },
        traces: []
    }, _chart)
    const el = initChart(chart.layout)
    chart.el = el

    chart.addTrace = (trace) => {
        chart.traces.push(trace)
        Plotly.addTraces(el, [trace.settings])
    }

    chart.removeTrace = (trace) => {
        Plotly.deleteTraces(el, trace.index)
    }

    chart.updateTraces = _ => {
        const newTraceDatas = {
            x: chart.traces.map(t => t.dataBuffer.map(b => b.timeStamp)),
            y: chart.traces.map(t => t.dataBuffer.map(b => b.value)),
            indicies: chart.traces.map((t, i) => i)
        }
        appendTraces(el, newTraceDatas)
        chart.traces.forEach(t => t.clearDataBuffer())
    }

    const intervalId = setInterval(chart.updateTraces, 100);
    chart.destroy = _ => {
        Plotly.purge(el)
        clearInterval(intervalId)
    }


    return chart
}



function initChart(layout) {
    const el = document.createElement("div")
    document.getElementById('plot-root').appendChild(el)
    Plotly.newPlot(el, [], layout)
    return el
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