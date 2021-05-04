import * as dev from "./coreBinding";

let LED = dev.getPinLED();

function setup(): void {
    dev.pinMode(LED, dev.OUTPUT);
}

function run(): void {
    // dev.digitalWrite(LED, dev.HIGH);
    // dev.delay(3000);
    dev.digitalWrite(LED, dev.LOW);
    // dev.delay(100);
    // dev.digitalWrite(LED, dev.HIGH);
    // dev.delay(3000);
}




/*
 * Entry point
 */
export function _start(): void {
    setup();
    while (1) {
        run();
    }
}


// import 'wasi';
// import { Console } from 'as-wasi';



// Console.log("hello world")

// // function helloworld(): void {
// //     const a = 1
// //     const b = 2
// //     Console.log((a + b).toString())
// //     // console.log((a + b).toString());
// // }

// // helloworld()