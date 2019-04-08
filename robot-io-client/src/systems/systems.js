// const SocketClient = require('./socketClient');
// const DataParser = require('./dataParser');
import SocketClient from './socketClient';
import DataStore from './dataStore';
import DataInputTest from './dataInputTest';

// module.exports = createRobotIOClient
import ChartManager from './chartManager';
export default createSystems


function createSystems() {
    const dataStore = DataStore()
    const socketClient = SocketClient()
    const chartManager = ChartManager()
    dataStore.onData.addListener(chartManager.addData)
    dataStore.onReset.addListener(chartManager.resetData)
    socketClient.onData.addListener(dataStore.addData)

    const dataInputTest = DataInputTest()
    dataInputTest.onData.addListener(dataStore.addData)
    // dataInputTest.onReset.addListener(dataStore.resetData)
    // dataInputTest.onData.addListener(chartManager.addData)



    const systems = {
        chartManager,
        dataInputTest,
        socketClient,
        dataStore
    }
    window.systems = systems



    return systems
}
