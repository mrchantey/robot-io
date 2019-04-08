const argvIn = require('minimist')(process.argv.slice(2));
import Server from './server';

const argv = Object.assign({ port: 8080, hostname: "127.0.0.1" }, argvIn)

export default createRobotIO
module.exports = createRobotIO

function createRobotIO() {

    const server = Server(argv)
    const robotIO = {
        server,
        addMiddleware
    }

    function addMiddleware(middleware) {
        server.onData.addListener(middleware.sendData)
        middleware.onData.addListener(server.sendData)
        //hack so that robot-io-device can attach self to server
        //server.use(deviceApp,'./device')
        // if (middleware.onConnect !== undefined)
        // middleware.onConnect(server)
    }
    return robotIO
}



if (require.main === module) {

    const robotIO = createRobotIO()
    // testSendData()


    function testSendData() {
        robotIO.server.sendData({ message: "wake up!" })
        setTimeout(_ => {
            robotIO.server.sendData({
                init: [
                    { type: 'chart', name: 'Accelerometer', id: 0 },
                    { type: 'trace', name: 'x', id: 1, chartId: 0, settings: { mode: 'lines+markers' } },
                    { type: 'trace', name: 'y', id: 2, chartId: 0 },
                    { type: 'trace', name: 'z', id: 3, chartId: 0 },]
            })
            robotIO.server.sendData({
                init: [
                    { type: 'chart', name: 'Gyroscope', id: 1 },
                    { type: 'trace', name: 'x', id: 4, chartId: 1, settings: { mode: 'lines+markers' } },
                    { type: 'trace', name: 'y', id: 5, chartId: 1 },
                    { type: 'trace', name: 'z', id: 6, chartId: 1 }]
            })

            let valaX = 0
            let valaY = 0
            let valaZ = 0
            let valgX = 0
            let valgY = 0
            let valgZ = 0
            const beginMillis = Date.now()
            setInterval(() => {
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
                robotIO.server.sendData(data)
            }, 100);
        }, 3000)
    }
}