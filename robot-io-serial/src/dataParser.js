const mpuPlotter = require('./mpuPlotter');

module.exports = {
    parseData
}

function parseData(data) {
    if (!data.timeStamp) {
        console.warn('no timestamp found');
        return
    }
    if (data.mpuData) {
        // console.log('mpu data found');
        mpuPlotter.plotMpu(data.mpuData, data.timeStamp);
    }
}
