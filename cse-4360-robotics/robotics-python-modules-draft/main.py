from robotics import Robot
import numpy as np
import matricies

left_motor = 1
right_motor = 1
robot = Robot(left_motor, right_motor)


# Example List of Transformations
transformations = [('T', 1,0), ('R', 180), ('T', 1, 0)]


commands = matricies.transformations_to_commands(transformations, robot)






