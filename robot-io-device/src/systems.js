

const SensorsSystem = require('./sensors/sensors');
const UiSystem = require('./ui/ui');

module.exports = initSystems

function initSystems() {

    const systems = {
        sensors: SensorsSystem(),
        ui: UiSystem()
    }

    window.systems = systems
}