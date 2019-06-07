#!/usr/bin/env python3

# import ev3dev2
from commanderBase import CommanderBase
from ev3dev2 import sound
from ev3dev2 import motor
from time import sleep
# from ev3dev2.motor import LargeMotor,OUTPUT_A,OUTPUT_B,OUT
# from ev3dev2.motor import SpeedDPS, SpeedRPM, SpeedRPS, SpeedDPM


# default_config = {
#     "largeMotor":"OUTPUT_B"

# }

class Ev3Commander(CommanderBase):
    def __init__(self):

        self.sound = sound.Sound()
        self.leftWheel = motor.LargeMotor(motor.OUTPUT_B)
        self.rightWheel = motor.LargeMotor(motor.OUTPUT_C)
        self.spinner = motor.MediumMotor(motor.OUTPUT_A)

    def setmotor(self, port, speed):
        if port == 'a':
            self.spinner.on(speed)
        if port == 'b':
            self.leftWheel.on(speed)
        if port == 'c':
            self.rightWheel.on(speed)

    def playtone(self, frequency, duration):
        self.sound.play_tone(frequency, duration)


if __name__ == "__main__":
    commander = Ev3Commander()
    # commander.playtone(440, 1)
    commander.setmotor('a', 30)
    commander.setmotor('b', 30)
    commander.setmotor('c', 30)
    sleep(1)
    commander.setmotor('a', 0)
    commander.setmotor('b', 0)
    commander.setmotor('c', 0)
