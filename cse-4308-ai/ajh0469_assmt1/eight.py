import nodes as n
import copy


# Check if node - state is equal to goal state
def goal_test(node, goal_state):
    return node.state == goal_state


# Function finds children nodes of current node
def generate_next_states(node):

    # Set current state and find index of blank tile
    curr_state = node.state
    blank_index = curr_state.index(0)

    # Create a list to store the next states
    next_states = []

    # If the blank tile can move up ...
    if blank_index not in [0, 1, 2]:

        # Create a copy of the current state and swap blank and numbered tile
        next_state = copy.deepcopy(curr_state)
        next_state[blank_index], next_state[blank_index - 3] = next_state[blank_index - 3], next_state[blank_index]

        # Append the new state to the list of next states and mark blank tile's action
        new_node = n.Node(next_state)
        next_states.append(new_node)
        new_node.actions.append('UP')

    # If the blank tile can move down ...
    if blank_index not in [6, 7, 8]:

        # Create a copy of the current state and swap blank and numbered tile
        next_state = copy.deepcopy(curr_state)
        next_state[blank_index], next_state[blank_index + 3] = next_state[blank_index + 3], next_state[blank_index]

        # Append the new state to the list of next states and mark blank tile's action
        new_node = n.Node(next_state)
        next_states.append(new_node)
        new_node.actions.append('DOWN')

    # If the blank tile can move left ...
    if blank_index not in [0, 3, 6]:

        # Create a copy of the current state and swap blank and numbered tile
        next_state = copy.deepcopy(curr_state)
        next_state[blank_index], next_state[blank_index - 1] = next_state[blank_index - 1], next_state[blank_index]

        # Append the new state to the list of next states and mark blank tile's action
        new_node = n.Node(next_state)
        next_states.append(new_node)
        new_node.actions.append('LEFT')

    # If the blank tile can move right ...
    if blank_index not in [2, 5, 8]:

        # Create a copy of the current state and swap blank and numbered tile
        next_state = copy.deepcopy(curr_state)
        next_state[blank_index], next_state[blank_index + 1] = next_state[blank_index + 1], next_state[blank_index]

        # Append the new state to the list of next states and mark blank tile's action
        new_node = n.Node(next_state)
        next_states.append(new_node)
        new_node.actions.append('RIGHT')

    # Return the list of next states
    return next_states

