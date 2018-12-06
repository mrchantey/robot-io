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

    handleDataTest = (e) => {

        if (this.state.isTesting === false) {
            this.setState({ testText: "End Data Test", isTesting: true })
            window.systems.dataInputTest.begin()

        } else {
            this.setState({ testText: "Begin Data Test", isTesting: false })
            window.systems.dataInputTest.end()
        }
    }

    handleLoadData() {
        console.log('loading data');
        DataUtility.UploadAsync().then(data => {
            window.systems.dataStore.setData(data)
        })
    }

    handleLoadDataRealtime = (e) => {
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

    handleSaveData() {
        console.log('saving data');
        const data = window.systems.dataStore.getData()
        DataUtility.Download(data)
        // console.log();
    }
    render() {
        return (
            <div>
                <h2>File</h2>
                <button onClick={this.handleSaveData}>Save</button>
                <button onClick={this.handleLoadData}>Load</button>
                <button onClick={this.handleLoadDataRealtime}>{this.state.realtimeText}</button>
                <button onClick={this.handleDataTest}>{this.state.testText}</button>
            </div>)
    }

}

export default FileUI