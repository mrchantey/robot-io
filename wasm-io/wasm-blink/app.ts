import * as dev from "./arduino";

let LED = dev.getPinLED();

function setup(): void {
  dev.pinMode(LED, dev.OUTPUT);
}

function run(): void {
  // dev.digitalWrite(LED, dev.HIGH);
  // dev.delay(1000);
  dev.digitalWrite(LED, dev.LOW);
  dev.delay(5000);
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
