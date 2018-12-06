import React, { Component } from 'react'

class RobotHeading extends Component {
    constructor(props) {
        super(props)
        this.state = { now: Date.now() }
    }

    componentDidMount() {
        this.timerID = setInterval(() => {
            this.tick()
        }, 0);
    }

    componentWillUnmount() {
        clearInterval(this.timerID)
    }

    tick() {
        this.setState({
            now: Date.now()
        })
        // this.state.now = Date.now()
    }

    render() {
        // let time = Date.now()
        // console.dir(this);

        return (
            <h1>Robot IO</h1>
            // <div className="robot-heading">
            // {`Robot IO, time is ${this.state.now}`}
            // </div >
        )
    }



}

export default RobotHeading