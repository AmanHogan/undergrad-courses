import nodes as nodes
import sys

sys.setrecursionlimit(1000000)

nodes_popped = 0
nodes_expanded = 0
nodes_generated = 0
max_fringe_size = 0
goal_path = []


class Node:
    def __init__(self, state):
        self.children = []
        self.parent = None
        self.state = state
        self.actions = []
        self.rel_cost = 0
        self.cum_cost = 0
        self.node_depth = 0
        self.heuristic_1 = 0
        nodes.nodes_generated = nodes.nodes_generated + 1


sum = 0
def traverse_goal_path(node):
    goal_path.append(node)
    if node.parent:
        traverse_goal_path(node.parent)


def find_goal_path(node):
    traverse_goal_path(node)
    goal_path.reverse()

def print_path_details_dfs():
    file_handle = open('dfs.txt', 'w')
    file_handle.write(f'Nodes Popped: {nodes_popped}\nNodes Expanded: {nodes_expanded}\nNodes generated: {nodes_generated}\n')
    file_handle.write(f'Max Fringe Size: {max_fringe_size}\nSolution found at depth: {len(goal_path) - 1}\n')
    file_handle.write(f'Steps:')

    # Flip directions to print directions them relative to non-blank tile
    for node in goal_path:
        if node.parent:
            if 'UP' in node.actions:
                file_handle.write(f'Move {node.rel_cost} DOWN\n')
            elif 'DOWN' in node.actions:
                file_handle.write(f'Move {node.rel_cost} UP\n')
            elif 'RIGHT' in node.actions:
                file_handle.write(f'Move {node.rel_cost} LEFT\n')
            elif 'LEFT' in node.actions:
                file_handle.write(f'Move {node.rel_cost} RIGHT\n')
    file_handle.write('\n\n')
    file_handle.close()

def print_path_details():
    print(f'Nodes Popped: {nodes_popped}\nNodes Expanded: {nodes_expanded}\nNodes generated: {nodes_generated}')
    print(f'Max Fringe Size: {max_fringe_size}\nSolution found at depth {len(goal_path) - 1}')
    print(f'Steps:')

    # Flip directions to print directions them relative to non-blank tile
    for node in goal_path:
        if node.parent:
            if 'UP' in node.actions:
                print(f'Move {node.rel_cost} DOWN')
            elif 'DOWN' in node.actions:
                print(f'Move {node.rel_cost} UP')
            elif 'RIGHT' in node.actions:
                print(f'Move {node.rel_cost} LEFT')
            elif 'LEFT' in node.actions:
                print(f'Move {node.rel_cost} RIGHT')
    print('\n\n')


def heuristic_1(node, goal_state):
    h = 0
    state = node.state
    distance = 0
    for i in range(len(state)):
        if state[i] != 0:
            distance = (abs(i // 3 - goal_state.index(state[i]) // 3) + abs(i % 3 - goal_state.index(state[i]) % 3))
            h += distance * node.rel_cost
    node.heuristic_1 = h
    return h


def log_node_to_output(f, node, fringe, visited):
    # Log node details to output file
    f.write(
        f'Generating successors to state = {node.state} | action = {node.actions} g(n) = {node.cum_cost} | d = {node.node_depth} | h(n) = {node.heuristic_1} | f(n) = {node.heuristic_1 + node.cum_cost}\n')
    if node.parent:
        f.write(f'Parent is Pointer to {node.parent.state}\n')
    f.write(f'{len(node.children)} successors generated\n')
    f.write(f'Closed: {visited}\n')
    f.write(f'Fringe: \n')
    fringe_string = ''
    for i in fringe:
        fringe_string = fringe_string + str(i.state) + ','
    f.write(f'{fringe_string}\n')
    f.write('---------------------------\n\n')


def log_root_to_output(f, arguments):
    # Open and output file and log information in file
    f.write(f'Command-Line arguments: {arguments}\nMethod Selected: {arguments[3]}\nRunning {arguments[3]}')


def update_path_costs(path_cost, next_node, node):
    path_cost[tuple(next_node.state)] = path_cost[tuple(node.state)] + next_node.state[node.state.index(0)]
    next_node.cum_cost = path_cost[tuple(next_node.state)]
    next_node.rel_cost = next_node.state[node.state.index(0)]
    next_node.node_depth = node.node_depth + 1
