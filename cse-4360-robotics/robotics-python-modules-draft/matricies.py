import numpy as np
import math
import matplotlib.pyplot as plt
import robotics.py


def translation_matrix(dx, dy):
    return np.array([[1, 0, dx], [0, 1, dy], [0, 0, 1]])

def rotation_matrix(theta_deg):
    theta_rad = np.deg2rad(theta_deg)
    cos_theta = np.cos(theta_rad)
    sin_theta = np.sin(theta_rad)
    return np.array([[cos_theta, -sin_theta, 0], [sin_theta, cos_theta, 0], [0, 0, 1]])

def transformation_matrix(dx, dy, theta_deg):
    translation = translation_matrix(dx, dy)
    rotation = rotation_matrix(theta_deg)
    return np.dot(translation, rotation)

def combine_transformations(transformations):
    result = np.eye(3)  # Initialize with the identity matrix

    for transformation in transformations:
        if transformation[0] == 'T':
            dx, dy = transformation[1:]
            translation_matrix = np.array([[1, 0, dx],
                                           [0, 1, dy],
                                           [0, 0, 1]])
            result = np.dot(result, translation_matrix)
        elif transformation[0] == 'R':
            theta_deg = transformation[1]
            rotation_matrix = np.array([[np.cos(np.deg2rad(theta_deg)), -np.sin(np.deg2rad(theta_deg)), 0],
                                        [np.sin(np.deg2rad(theta_deg)), np.cos(np.deg2rad(theta_deg)), 0],
                                        [0, 0, 1]])
            result = np.dot(result, rotation_matrix)

    return result

def get_orientation(matrix):
    angle_rad = np.arctan2(matrix[1, 0], matrix[0, 0])
    angle_deg = np.rad2deg(angle_rad)
    return angle_deg

def transformations_to_commands(transformations):
    commands = []
    current_angle = 0
    for transformation in transformations:
        if transformation[0] == 'T':
            dx, dy = transformation[1], transformation[2]
            distance = np.sqrt(dx ** 2 + dy ** 2)
            commands.append(("move", distance))
        elif transformation[0] == 'R':
            angle_deg = transformation[1]
            current_angle += angle_deg
            commands.append(("turn", current_angle))
    return commands


def execute_commands(commands):
    for command in commands:
        action, value = command
        if action == 'move':
            robot.move(value)
        elif action == 'turn':
            robot.turn(value)



# Example usage:
transformations = [('T', 1,0), ('R', 180), ('T', 1, 0)]

commands = transformations_to_commands(transformations)
for command in commands:
    print(command)


# Example usage:
# transformations = [('T', 0, 0), ('R', 180), ('T', 0, 0), ('T', 1, 1), ('T', 0, 0)]
# final_matrix = combine_transformations(transformations)

# final_position = np.dot(final_matrix, np.array([0, 0, 1]))  # Starting position at (0, 0)
# final_x, final_y, _ = final_position

# final_orientation_deg = get_orientation(final_matrix)

# print("Final Position (x, y):", final_x, final_y)
# print("Final Orientation (degrees):", final_orientation_deg)