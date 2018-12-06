const dataParser = require('./dataParser');


module.exports = {
    parseBytes

}


/*
0   -code
1   -timestamp 0
2   -timestamp 1
3   -timestamp 2
4   -timestamp 3
5   -acc x
6   -acc y
7   -acc z
8   -gyro x
9   -gyro y
10  -gyro z
11  -temp


*/


function parseBytes(bytes) {
    // console.log('parsing mpu data');
    // console.log(bytes);


    const timeStamp = dataParser.bytesToLongNumber(bytes, 1)

    return {
        mpuData: {
            acc: {
                x: dataParser.unsignedToSignedByte(bytes[5]),
                y: dataParser.unsignedToSignedByte(bytes[6]),
                z: dataParser.unsignedToSignedByte(bytes[7]),
            }, gyro: {
                x: dataParser.unsignedToSignedByte(bytes[8]),
                y: dataParser.unsignedToSignedByte(bytes[9]),
                z: dataParser.unsignedToSignedByte(bytes[10]),
            }, temp: bytes[11]
        }, timeStamp
    }

}