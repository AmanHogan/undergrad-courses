import matplotlib.pyplot as plt

# Author: Aman Hogan-Bailey
# MavID: 1001830469
# Date: 03/2023

graph_names = []

######################################################
# Args:
#   x - list of array sizes
#   y - runtimes of arrays
#   graph_name - the type of sorting algorithm used
#
# Function:
#   Plots a graph showing the input sizes vs runtimes
#   in microseconds
#
# Returns:
#   None
#######################################################
def graphing(x, y, graph_name):

    graph_names.append(graph_name)
    print(f'Graphing {graph_names} sort ... ')
    
    plt.scatter(x, y)
    plt.xlabel('Array Size (x) [#]')
    plt.ylabel('Runtime (y) [microseconds]')
    plt.title(f'Input size VS Runtime {graph_name} sort ')
    plt.savefig(f"{graph_name} sort",dpi=300)
    plt.show()



