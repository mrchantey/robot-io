

const Serial = require('./index');


const serial = Serial()
serial.onData.addListener(data => {
    console.log('data received');
    console.dir(data);
})
