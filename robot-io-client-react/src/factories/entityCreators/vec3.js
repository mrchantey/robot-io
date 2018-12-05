import CreateChart from '../chartCreator';
import * as entCreator from './entity'
import circleAssign from 'circle-assign';

export let shortName = "vec3"
export let name = "Vector 3"

export function create(_ent) {

    const ent = circleAssign({
        name,
        shortName,
        groupData: {
            layout: {
                title: name,
                showlegend: true,
                xaxis: { title: "time (s)" },
                yaxis: { title: "units" },
                // plot_bgcolor: '#1E1E1E',
            }
        },
        addData,
        resetData,
        traceDatas: [
            {
                name: "x",
                line: {
                    color: 'rgb(255,0,0)'
                }
            },
            {
                name: "y",
                line: {
                    color: 'rgb(0,255,0)'
                }
            },
            {
                name: "z",
                line: {
                    color: 'rgb(0,0,255)'
                }
            }
        ]
    }, _ent)
    ent.groupData.layout.title = ent.name

    const chart = CreateChart(ent.groupData, ent.traceDatas)

    function addData(data, timeStamp) {
        const traceDatas = {
            x: [timeStamp, timeStamp, timeStamp],
            y: [data.x, data.y, data.z]
        }
        chart.appendTraceDataBuffers(traceDatas)
    }

    function resetData() {
        chart.resetTraces()
    }

    ent.chart = chart


    return entCreator.create(ent)
}

