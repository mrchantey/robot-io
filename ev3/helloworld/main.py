#!/usr/bin/env python3

import debug_ev3
import time
from neckMotor import NeckMotor
from tank import Tank
from depthSensor import DepthSensor

startTime = time.time()
ellapsedTime = 0
speed = 50

debug_ev3.pc_print('beginning program..')

neckMotor = NeckMotor('D')
neckMotor.Start()

tank = Tank(speed)
tank.Forward()

depthSensor = DepthSensor()

while ellapsedTime < 20:
    # while True:
    neckMotor.Update()
    ellapsedTime = time.time() - startTime
    depth = depthSensor.GetReading()
    if(depth < 20):
        debug_ev3.pc_print("turning")
        tank.Turn()
    else:
        tank.Forward()
        debug_ev3.pc_print("forward")
    # time.sleep(0.1)

neckMotor.End()

debug_ev3.pc_print('ending program..')
