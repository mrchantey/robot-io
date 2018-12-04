module.exports = createJsonBufferParser

function createJsonBufferParser() {
    // let incompleteMessage = ""
    // let incompleteMessageDepth = 0;

    let jsonStr = ""
    let jsonBufferInProgress = false

    function parseBuffer(buf) {
        const bufStr = buf.toString()
        for (let i = 0; i < bufStr.length; i++) {
            const chr = bufStr.charAt(i)
            if (chr === '<') {
                jsonBufferInProgress = true
            } else if (chr === '>' && jsonStr != '') {
                jsonBufferInProgress = false
                onMessageComplete(jsonStr)
                jsonStr = ''
            }
            else if (jsonBufferInProgress === true) {
                jsonStr += chr
            }
        }
    }
    const bufParser = {
        parseBuffer,
        onMessageCallback: msg => {
            console.log(`message received:`)
            console.dir(msg)
        }
    }
    function onMessageComplete(msg) {
        try {
            console.log('parsing message');
            msg = msg.replace('\r\n', '')
            console.dir(msg);
            const obj = JSON.parse(msg)
            // console.dir(obj);
            bufParser.onMessageCallback(obj);
        } catch (err) {
            console.error(err);
        }
    }
    return bufParser
}

            // if (chr === "{") {
            //     incompleteMessage += chr;
            //     incompleteMessageDepth++;
            // } else if (incompleteMessage !== "") {
            //     incompleteMessage += chr;
            //     if (chr === "}") {
            //         incompleteMessageDepth--;
            //         if (incompleteMessageDepth === 0) {
            //             onMessageComplete(incompleteMessage)
            //             incompleteMessage = ""
            //         }
            //     }
            // }