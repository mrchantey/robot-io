import CreateDataEntity from '../factories/dataEntityCreator';

export default createDataEntityManager


function createDataEntityManager() {

    const entities = []

    const manager = {
        entities,
        addData,
        resetData
    }


    function addData(data) {
        // console.log(data);
        // console.log(`data received`);
        // console.dir(data);
        if (data.timeStamp === undefined) {
            console.warn('no timestamp found');
            return
        }

        Object.keys(data)
            .filter(k => k !== 'timeStamp')
            .forEach(k => {
                // if (data.uuid === undefined) data.uuid = 0
                let entity = entities.find(ent => ent.shortName === k)
                if (entity === undefined) {
                    entity = CreateDataEntity(k, data[k])
                    entities.push(entity)
                }
                entity.addData(data[k], data.timeStamp)
            })
    }

    function resetData() {
        entities.forEach(e => e.resetData())
    }
    return manager
}