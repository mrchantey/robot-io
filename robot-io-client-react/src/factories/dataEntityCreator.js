import * as mpu from './entityCreators/mpu';
import * as vec3 from './entityCreators/vec3';
// import * as acc from './entityCreators/accelerometerEntityCreator';
// import * as gyro from './entityCreators/gyroscopeEntityCreator';

const dataEntityTypes = [
    mpu,
    vec3,
    // acc,
    // gyro
]

export default function createDataEntity(key, data) {

    const dataT = dataEntityTypes.find(t => t.shortName === key)
    if (dataT === undefined) {
        console.warn(`unknown data entity type: ${key}`);
    } else {
        return dataT.create(data)
    }
    // return
}