


// if (require === undefined)
// export default createEvent
// else
module.exports = createEvent
function createEvent() {
    const listeners = []

    function invoke(params) {
        listeners.forEach(l => l(params))
    }

    function addListener(listener) {
        listeners.push(listener)
    }

    return {
        addListener,
        invoke
    }

}