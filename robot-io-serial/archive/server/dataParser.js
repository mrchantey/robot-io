

module.exports = {
    stringBitsToByte,
    stringBitsToBytes,
    bytesToLongNumber,
    unsignedToSignedByte
}


function bytesToLongNumber(bytes, startIndex = 0) {
    let a = bytes[startIndex] << 24;
    let b = bytes[startIndex + 1] << 16;
    let c = bytes[startIndex + 2] << 8;
    let d = bytes[startIndex + 3] << 0;
    return a + b + c + d;
}

function unsignedToSignedByte(val) {
    return val <= 127 ? val : val - 256;

}

function stringBitsToBytes(msg) {
    const numBytes = msg.length / 8
    const bytes = [];
    for (let byteI = 0; byteI < numBytes; byteI++) {
        const bitI = byteI * 8;
        bytes[byteI] = stringBitsToByte(msg, bitI)

    }
    // console.log(`parsing ${numBytes} bytes`);
    // console.log(bytes);
    return bytes
}



function stringBitsToByte(msg, startIndex) {
    let num = 0;
    num += msg.charAt(startIndex) == "0" ? 0 : 128
    num += msg.charAt(startIndex + 1) == "0" ? 0 : 64
    num += msg.charAt(startIndex + 2) == "0" ? 0 : 32
    num += msg.charAt(startIndex + 3) == "0" ? 0 : 16
    num += msg.charAt(startIndex + 4) == "0" ? 0 : 8
    num += msg.charAt(startIndex + 5) == "0" ? 0 : 4
    num += msg.charAt(startIndex + 6) == "0" ? 0 : 2
    num += msg.charAt(startIndex + 7) == "0" ? 0 : 1
    return num
}

function testBytesToLongNumber() {
    const bytes = [0, 0, 0, 0]
    for (let i0 = 0; i0 < 255; i0++) {
        bytes[3] = i0

    }
}


if (require.main === module) {


}
