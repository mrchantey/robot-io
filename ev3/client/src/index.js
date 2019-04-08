// const request = require('request');


window.addEventListener('load', _ => {
    const el = document.createElement('div')
    el.innerHTML = 'hello world!'
    document.body.appendChild(el)
    console.log('hello world!');
})


const speed = 60
let keyispressed = false
window.addEventListener('keydown', e => {
    if (keyispressed === true)
        return
    keyispressed = true
    // console.dir(e);
    switch (e.code) {
        case "ArrowLeft":
            console.log("left");
            sendCommand(`command:setmotor,port:b,speed:${speed}`)
            break
        case "ArrowRight":
            console.log("right");
            sendCommand(`command:setmotor,port:b,speed:${-speed}`)
            break
        case "ArrowUp":
            console.log("up");
            break
        case "ArrowDown":
            console.log("down");
            break
        case "Space":
            console.log("space");
            sendCommand(`command:setmotor,port:a,speed:${-speed}`)
        default:
            return
    }
})
window.addEventListener('keyup', e => {
    keyispressed = false
    // console.dir(e);
    switch (e.code) {
        case "ArrowLeft":
            console.log("left");
            sendCommand(`command:setmotor,port:b,speed:0`)
            break
        case "ArrowRight":
            console.log("right");
            sendCommand(`command:setmotor,port:b,speed:0`)
            break
        case "ArrowUp":
            console.log("up");
            break
        case "ArrowDown":
            console.log("down");
            break
        case "Space":
            console.log("space");
            sendCommand(`command:setmotor,port:a,speed:${0}`)
        default:
            return
    }
})

function sendCommand(command) {
    const url = `http://169.254.42.5:5000/${command}`
    console.log(`fetching url: ${url}`);
    fetch(url)
        .then(res => res.json())
        .then(json => console.log(json))
}


