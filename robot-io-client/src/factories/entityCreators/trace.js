import circleAssign from 'circle-assign';

export default function createTrace(_trace, chart) {
    const index = chart.el.data.length
    const trace = circleAssign(GetDefaultSettings(_trace), _trace)
    trace.chart = chart
    trace.index = index
    trace.appendDataBuffer = (value, timeStamp) => {
        trace.dataBuffer.push({ value, timeStamp })
    }

    trace.clearDataBuffer = _ => {
        trace.dataBuffer.length = 0
    }

    trace.destroy = _ => {
        chart.removeTrace(trace)
    }

    //this is async
    chart.addTrace(trace)
    return trace
}


function GetDefaultSettings(_trace, index) {
    const name = _trace.name === undefined ? `data ${index}` : _trace.name
    const trace = {
        settings: {
            name: name,
            type: 'scattergl',
            // type: 'line',
            mode: 'lines',
            x: [],
            y: [],
            line: {
                // color: 'rgb(219, 64, 82)',
                width: 3
            },
        },
        dataBuffer: [],
    }
    if (_trace.name === 'x' || _trace.name === 'r' || _trace.name === 'red')
        trace.settings.line.color = 'rgb(255, 0, 0)'
    if (_trace.name === 'y' || _trace.name === 'g' || _trace.name === 'green')
        trace.settings.line.color = 'rgb(0, 255, 0)'
    if (_trace.name === 'z' || _trace.name === 'b' || _trace.name === 'blue')
        trace.settings.line.color = 'rgb(0, 0, 255)'
    return trace
}