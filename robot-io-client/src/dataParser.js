const dataTypes = require('./dataTypes/dataTypes');


module.exports = createDataParser




function createDataParser(doMpu) {

    const dataInstances = []
    // console.dir(dataTypes);

    function parseData(data) {
        // console.log(`data received`);
        // console.dir(data);
        if (!data.timeStamp) {
            console.warn('no timestamp found');
            return
        }
        Object.keys(data)
            .filter(k => k !== 'timeStamp')
            .forEach(k => {
                const matchingType = dataTypes.find(t => t.name === k)
                if (matchingType === undefined) {
                    console.warn(`unknown data type : ${k}`);
                } else {
                    const inst = dataInstances.find(i => i.name === k)
                    if (inst === undefined) {
                        dataInstances.push(matchingType.createInstance())
                    } else {
                        inst.onData(data[k], data.timeStamp)
                    }
                }
            })
    }

    return {
        dataInstances,
        parseData
    }
}

