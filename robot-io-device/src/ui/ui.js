



module.exports = createUISystem


function createUISystem() {
    createStartStopButton()
    createResetButton()


}


function createResetButton() {
    const elt = document.createElement('button')
    elt.innerText = "Reset"
    document.body.appendChild(elt)
    elt.addEventListener('mouseup', _ => {
        window.systems.sensors.reset()
    })
}

function createStartStopButton() {

    let state = false
    const elt = document.createElement('button')
    elt.innerText = "Start"
    document.body.appendChild(elt)
    elt.addEventListener('mouseup', _ => {
        if (state === false) {
            window.systems.sensors.start()
            elt.innerText = "Stop"
        } else {
            window.systems.sensors.stop()
            elt.innerText = "Start"
        }
        state = !state
        // console.log('bang')
    })
}