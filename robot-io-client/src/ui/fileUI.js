import React, { Component } from 'react';
import DataUtility from '../systems/dataUtility'


class FileUI extends Component {

    constructor(props) {
        super(props)

        this.state = {
            testText: "Begin Data Test",
            isTesting: false,
            realtimeText: "Begin Realtime Load",
            isRealtime: false
        }
    }


    componentDidMount() {

    }
    componentWillUnmount() {

    }

    handleTest = (e) => {

        if (this.state.isTesting === false) {
            this.setState({ testText: "End Data Test", isTesting: true })
            window.systems.dataInputTest.begin()

        } else {
            this.setState({ testText: "Begin Data Test", isTesting: false })
            window.systems.dataInputTest.end()
        }
    }

    handleReset() {
        console.log('resetting data..');
        window.systems.dataStore.resetData()
        window.systems.dataInputTest.end()
    }

    handleLoad() {
        console.log('loading data');
        DataUtility.UploadAsync().then(data => {
            window.systems.dataStore.setData(data)
        })
    }

    handleLoadRealtime = (e) => {
        console.log('loading data realtime');


        const startRealtime = () => {
            this.setState({ realtimeText: "End Realtime Load", isRealtime: true })
            DataUtility.UploadAsync().then(data => {
                window.systems.dataStore.setDataRealtime(data, stopRealtime)
            })

        }
        const stopRealtime = () => {
            this.setState({ realtimeText: "Begin Realtime Load", isRealtime: false })
        }

        if (this.state.isRealtime === false) {
            startRealtime()
        } else {
            stopRealtime()
            window.systems.dataStore.stopDataRealtime()
        }
    }

    handleSave() {
        console.log('saving data');
        const data = window.systems.dataStore.getData()
        DataUtility.Download(data)
        // console.log();
    }
    render() {
        return (
            <div>
                <h2>File</h2>
                <button onClick={this.handleReset}>Reset</button>
                <button onClick={this.handleSave}>Save</button>
                <button onClick={this.handleLoad}>Load</button>
                <button onClick={this.handleLoadRealtime}>{this.state.realtimeText}</button>
                <button onClick={this.handleTest}>{this.state.testText}</button>
            </div>)
    }

}

export default FileUI