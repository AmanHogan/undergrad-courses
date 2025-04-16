from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor, InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
import math

class Robot:

    TIRE_CIRC = 178
    FULL_ROTATION = 360
    RPM = 400
    ROBOT_LENGTH = 105
    DIST_BTWN_WHEELS = 155
    M_PI = 3.14159265359 

    def __init__(self, left_motor, right_motor):
        self.left_motor = left_motor
        self.right_motor = right_motor

    def move(self, distance):
        angle =  (distance / Robot.TIRE_CIRC) * Robot.FULL_ROTATION
        self.left_motor. run_angle(Robot.RPM, angle, wait=False)
        self.right_motor.run_angle(Robot.RPM, angle)
    
    def turn(self, angle):
        arc_length = 2 * Robot.M_PI * (Robot.DIST_BTWN_WHEELS/2) * (angle/360)
        new_angle =  (arc_length / Robot.TIRE_CIRC) * Robot.FULL_ROTATION

        self.left_motor. run_angle(Robot.RPM, -new_angle, wait=False)
        self.right_motor.run_angle(Robot.RPM, new_angle)


        left_motor. run_angle(rpm, angle, wait=False)
        right_motor.run_angle(rpm, angle)