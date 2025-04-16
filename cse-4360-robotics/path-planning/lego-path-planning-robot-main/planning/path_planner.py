"""Uses predefiend data on the robot in the globals file and plans a path to the goal using a* search algortihm
"""

import math
import rmath.micro_numpy as np
from globals.globals import *

ON_DESKTOP = False

# If running program on desktop import the matplot libraries
try:
    import matplotlib.pyplot as plt
    ON_DESKTOP = True
except ImportError:
    pass

################################ Node Class #################################################

class Node:
    """Node structure that keeps track of the path traveled
    """
    def __init__(self, x, y, cost, parent_index) -> None:
        self.x = x  # index of the grid
        self.y = y  # index of the grid
        self.cost = cost # heuristic cost of traveling
        self.parent_index = parent_index # parent of the current node

########################### Path Planner Class ###############################################

class PathPlanner:
    """Responsible for path planning and path finding. Uses a* search for finding the path.
    """
    def __init__(self, ox, oy, resolution, rr):
        """Initialize grid map for a star planning

        Args:
            ox (list[float]): x position list of Obstacles [m]
            oy (list[float]): y position list of Obstacles [m]
            resolution (float): size of the grid boxes used [m]
            rr (float): radius of the robot [m]
        """

        self.resolution = resolution # size of the grid boxes used
        self.rr = rr # radius of the robot [m]
        self.min_x, self.min_y = 0, 0 # Constraint of x position
        self.max_x, self.max_y = 0, 0 # Constraint of y position
        self.obstacle_map = None
        self.x_width, self.y_width = 0, 0
        self.motion = self.get_motion_model()
        self.calc_obstacle_map(ox, oy)

    def planning(self, sx, sy, gx, gy):
        """Implements path planning and finds the path from the start to goal
        while also avoid the obstacles.

        Args:
            sx (float): start x position [m]
            sy (float): start y position [m]
            gx (float): goal x position [m]
            gy (float): goal y position [m]

        Returns:
            rx (list[float]): x position list of the final path,
            ry (list[float]): y position list of the final path
        """

        # Get initial state - node, and keep track of max fringe size
        start_node = Node(self.calc_xy_index(sx, self.min_x), self.calc_xy_index(sy, self.min_y), 0.0, -1)
        goal_node = Node(self.calc_xy_index(gx, self.min_x), self.calc_xy_index(gy, self.min_y), 0.0, -1)

        # Queue to keep track of nodes and visited nodes
        fringe, visited_set = dict(), dict()
        fringe[self.calc_grid_index(start_node)] = start_node

        # While the queue is not empty ...
        while True:

            # No goal state found or fringe is empty
            if len(fringe) == 0:
                print("No solution or fringe was empty")
                break
            
            # Sort the fringe based on Heuristic
            c_id = min(fringe, key=lambda o: fringe[o].cost + self.calc_heuristic(goal_node, fringe[o]))
        
            current = fringe[c_id]

            # If the program is being compiled on desktop, show graph
            if ON_DESKTOP:

                try:
                    plt.plot(self.calc_grid_position(current.x, self.min_x), self.calc_grid_position(current.y, self.min_y), "xc")
                    
                    # for stopping simulation with the esc key.
                    plt.gcf().canvas.mpl_connect('key_release_event', lambda event: [exit(0) if event.key == 'escape' else None])
                    if len(visited_set.keys()) % 10 == 0:
                        plt.pause(0.001)

                except ImportError:
                    pass

            # If current state matches the goal state
            # Break and find which path reached that goal state
            if current.x == goal_node.x and current.y == goal_node.y:
                print("Goal was reached; Finding the path that found the goal")
                print("-----------------------")
                goal_node.parent_index = current.parent_index
                goal_node.cost = current.cost
                break

            # Pop node from queue
            del fringe[c_id]

            # Add popped node to visited
            visited_set[c_id] = current

            # Expand_grid search grid based on motion model
            for i, _ in enumerate(self.motion):
                node = Node(current.x + self.motion[i][0], current.y + self.motion[i][1], current.cost + self.motion[i][2], c_id)
                n_id = self.calc_grid_index(node)

                # If the node is not safe, do nothing
                if not self.verify_node(node):
                    continue

                if n_id in visited_set:
                    continue

                if n_id not in fringe:
                    fringe[n_id] = node  # discovered a new node
                else:
                    if fringe[n_id].cost > node.cost:
                        fringe[n_id] = node

        # Get list of r and y values for the final path
        rx, ry = self.calc_final_path(goal_node, visited_set)

        return rx, ry

    def calc_final_path(self, goal_node, visited_set):
        """Gets the final path x and y values from the nodes and visited sets

        Args:
            goal_node (Node): goal state of the path planner
            visited_set (dict): Nodes that have been visited

        Returns:
            rx (list[float]): x position list of the final path,
            ry (list[float]): y position list of the final path
        """

        # Generate final course
        rx, ry = [self.calc_grid_position(goal_node.x, self.min_x)], [self.calc_grid_position(goal_node.y, self.min_y)]
        
        parent_index = goal_node.parent_index
        
        while parent_index != -1:
            n = visited_set[parent_index]
            rx.append(self.calc_grid_position(n.x, self.min_x))
            ry.append(self.calc_grid_position(n.y, self.min_y))
            parent_index = n.parent_index

        print("Path Found")
        print("-----------------------")
        return rx, ry

    @staticmethod
    def calc_heuristic(n1, n2):
        """Euclidean distance heuristic

        Args:
            n1 (float): x node position
            n2 (float): y node position

        Returns:
            float: Euclidian Distance
        """
        w = 1.0  # weight of heuristic
        d = w * np.hypot(n1.x - n2.x, n1.y - n2.y)
        return d

    def calc_grid_position(self, index, min_position):
        pos = index * self.resolution + min_position
        return pos

    def calc_xy_index(self, position, min_pos):
        return round((position - min_pos) / self.resolution)

    def calc_grid_index(self, node):
        return (node.y - self.min_y) * self.x_width + (node.x - self.min_x)

    def verify_node(self, node):
        """Verifies that the node is actually a legal move in the grid.

        Args:
            node (Node): Node containing the positions and max

        Returns:
            Bool: True if legal move, False if not a legal move
        """
        px = self.calc_grid_position(node.x, self.min_x)
        py = self.calc_grid_position(node.y, self.min_y)

        if px < self.min_x:
            return False
        elif py < self.min_y:
            return False
        elif px >= self.max_x:
            return False
        elif py >= self.max_y:
            return False

        # collision check
        if self.obstacle_map[node.x][node.y]:
            return False

        return True

    def calc_obstacle_map(self, ox, oy):

        self.min_x = round(min(ox))
        self.min_y = round(min(oy))
        self.max_x = round(max(ox))
        self.max_y = round(max(oy))
        self.x_width = round((self.max_x - self.min_x) / self.resolution)
        self.y_width = round((self.max_y - self.min_y) / self.resolution)

        # NOTE: Printing out the values of the d vale can be very time consuming to the processor
        print("Calculating Obstacle Map (May take some time)")
        print("-----------------------")
        self.obstacle_map = [[False for _ in range(self.y_width)] for _ in range(self.x_width)]
        for ix in range(self.x_width):
            x = self.calc_grid_position(ix, self.min_x)
            for iy in range(self.y_width):
                y = self.calc_grid_position(iy, self.min_y)
                for iox, ioy in zip(ox, oy):
                    d = np.hypot(iox - x, ioy - y)
                    if d <= self.rr:
                        self.obstacle_map[ix][iy] = True
                        break
            
            print("Obstacle Map is ",round((ix/self.x_width)*100), "% Percent Complete...")

        print("Finished Drawing obstacle Map")
        print("-----------------------")

    @staticmethod
    def get_motion_model():
        """Defines the board/context of the robot for the state space search algorithms to work.

        Returns:
            list[list[float]]: Board that will be used for movement
        """
        # dx, dy, cost
        motion = [[1, 0, 1], [0, 1, 1], [-1, 0, 1], [0, -1, 1],
                  [-1, -1, math.sqrt(2)], [-1, 1, math.sqrt(2)], [1, -1, math.sqrt(2)], [1, 1, math.sqrt(2)]]

        return motion

##############################   Helper Functions   ###########################################

def get_final_path(rx, ry):
  """Gets the final path from the A* grid planning code.

  Args:
    rx: A list of the x coordinates of the final path.
    ry: A list of the y coordinates of the final path.

  Returns:
    A list of the final path in the format [(x, y), (x, y), ...].
  """

  final_path = []
  for i in range(len(rx)):
    final_path.append((round(rx[i],5), round(ry[i],5) ))

  return final_path

def draw_obstacle(ox, oy, x, y):
    """Draws a box around the given center point of an obstacle.
    Uses the predefined radius of the obstacles in globals.globals

    Args:
        ox (list[float]): _description_
        oy (list[float]): _description_
        x (float): x coord. of the center of obstacle
        y (float): y coord. of the center of obstacle
    """

    r = OBSTACLE_RADIUS

    ox.append(x-r)
    oy.append(y-r)
    ox.append(x-r)
    oy.append(y-0)
    ox.append(x-r)
    oy.append(y+r)
    ox.append(x-0)
    oy.append(y+r)
    ox.append(x+r)
    oy.append(y+r)
    ox.append(x+r)
    oy.append(y-0)
    ox.append(x+r)
    oy.append(y-r)
    ox.append(x+0)
    oy.append(y-r)

def draw_workspace(ox, oy):
    """Draws a rough estimate of the workspace of the robot. 
    Uses 1 + the rounded workspace lengths. EX: if real x workspace is 3.88, then
    the simulations x workspace would be 5

    Args:
        ox (list[float]): x coords of obstacles
        oy (list[float]): y coords of obstacles
    """

    x_t = [i*.07625 for i in range(65)]
    y_t = [3.05 for i in range(65)]
    x_b = [i*.07625 for i in range(65)]
    y_b = [0 for i in range(65)]
    x_r = [4.88 for i in range(41)]
    y_r = [i*.07625 for i in range(41)]
    x_l = [0 for i in range(41)]
    y_l = [i*.07625 for i in range(41)]
    

    for i in range(65):
        ox.append(x_t[i])
        oy.append(y_t[i])

        ox.append(x_b[i])
        oy.append(y_b[i])

    for i in range(41):
        ox.append(x_r[i])
        oy.append(y_r[i])

        ox.append(x_l[i])
        oy.append(y_l[i])


################################# Driver Function  ############################################

def start_path_planning():
    
    print("Starting the Path Planning")
    print("-----------------------")

    ox, oy = [], [] # x and y coords of obstacles to be avoided

    draw_workspace(ox, oy)
    for i in range(NUMBER_OF_OBS):
        draw_obstacle(ox, oy, OBS_POSITIONS[i][0], OBS_POSITIONS[i][1])

    # If running program on desktop, draw simulation
    if ON_DESKTOP: 
        try:
            plt.figure(figsize=(8,8))
            plt.title("Path Planning Grid", {'fontsize':14, 'fontweight': 'bold'})
            plt.xlabel("X coordinates (x) [m]", {'fontweight': 'bold'} )
            plt.ylabel("Y coordinates (y) [m]", {'fontweight': 'bold'})
            plt.plot(ox, oy, ".k")
            plt.plot(START_POSITION[0], START_POSITION[1], "og")
            plt.plot(GOAL_POSITION[0], GOAL_POSITION[1], "xb")

             # Create a list of the multiples of 0.305 up to 20.
            ticks = [i * 0.305 for i in range(1, 20)]
            plt.yticks(ticks)
            plt.xticks(ticks)
            plt.yticks()
            plt.xticks()
            plt.xlim(0, 4.88)
            plt.ylim(0, 3.05)
            plt.xticks(rotation=45, ha='right')
            plt.grid(True)
            # plt.axis("equal")


        except ImportError:
            pass
      
    a_star = PathPlanner(ox, oy, GRID_SIZE, ROBOT_RADIUS_M) # initialize a* object

    # Gets the Final Path
    rx, ry = a_star.planning(START_POSITION[0], START_POSITION[1], GOAL_POSITION[0], GOAL_POSITION[1]) 
    final_path = get_final_path(list(reversed(rx)),list(reversed(ry)))
    
    print("The Final path found: ")
    print(final_path)
    print("-----------------------")

    # If running program on desktop, draw simulation
    if ON_DESKTOP: 
        try:
            plt.plot(rx, ry, "-r")
            plt.savefig('planned_path.png')
            plt.pause(0.001)
            plt.show()
            
        except ImportError:
            pass

    return final_path

if __name__ == '__main__':
    print("-------------------- Start --------------------------")
    path_found = start_path_planning()
    print("--------------------  End  --------------------")