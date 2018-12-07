import JohnnyFiveInterface from './johnny-five-interface';

export default createJohnnyFiveMiddleware
module.exports = createJohnnyFiveMiddleware

const argvIn = require('minimist')(process.argv.slice(2));
const argv = {}
Object.assign(argv, argvIn)

function createJohnnyFiveMiddleware() {
    const johhnyFiveInterface = JohnnyFiveInterface(argv)
    const onDataListeners = []
    const onData = {
        addListener: listener => onDataListeners.push(listener),
        invoke: data => onDataListeners.forEach(l => l(data))
    }

    johhnyFiveInterface.onDataCallback = onData.invoke

    if (argv.debug === true) {
        onData.addListener(data => {
            console.log('data received');
            console.dir(data);
        });
    }

    const middleware = {
        onData,
        johhnyFiveInterface,
        sendData: johhnyFiveInterface.sendData
    }
    return middleware
}


if (require.main === module) {
    createJohnnyFiveMiddleware()
}