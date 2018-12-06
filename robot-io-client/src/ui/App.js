import React, { Component } from 'react';
import RobotHeading from './RobotHeading'
import FileUI from './fileUI';

import './App.css';

class App extends Component {
  render() {
    return (
      <div className="App">
        <RobotHeading isBuddy="yeababy" />
        <FileUI />
        {/* <header className="App-header">
          <p>
            Edit <code>src/App.js</code> and save to reload.
          </p>
        </header> */}
      </div>
    );
  }
}

export default App;
