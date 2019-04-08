# Captains log

### Serially
#### 10/12/2018

Achieved so far
- robot-io-server
- robot-io-client
- robot-io-johnny-five

Current projects
- robot-io-serial
- apa102 leds

All things are going fairly smoothly, the npm packages are working well with each other. At the moment the issue with the communication seems to be running out of memory with the robot-io-system on the arduino. This makes sense, they have a very small amount of dynamic memory.

Next attempt will be to store the strings more dynamically, and failing that, have each robot-io-communication component do its own `Serial.print()` This is a last resort as I imagine it will be quite slow.

The LEDs are going ok. It seems the APA102 led strips have trouble with the SPI communication when on external power.