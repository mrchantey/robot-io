


module.exports = {
    sendMessage,
    GetUUID,
    createDummySensor
    // GetTimeStamp
}


function sendMessage(data) {
    data.timeStamp = GetTimeStamp()
    if (window.socket)
        window.socket.sendData(data)
    else
        console.warn('socket not defined, message not sent');
}

function createDummySensor() {
    return {
        start: _ => console.log('dummy starting'),
        stop: _ => console.log('dummy stopping'),

    }
}


let uuidCount = 0
function GetUUID() {
    return uuidCount++
}

const startTime = Date.now()
function GetTimeStamp() {
    return (Date.now() - startTime) / 1000
}