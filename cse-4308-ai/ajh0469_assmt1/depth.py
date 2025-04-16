import eight as e
import nodes as n
import sys

sys.setrecursionlimit(1000000)

def dfs(initial_state, goal_state, arguments, dump_flag):
    f = None
    if dump_flag == 'true':
        f = open("output.txt", "w")
        n.log_root_to_output(f, arguments)

    # Stack to keep track of nodes and visited nodes
    fringe = []
    visited = set()

    # Get initial state - node, and keep track of max fringe size
    # Dictionary to store the path cost of each state discovered
    root = n.Node(initial_state)
    fringe.append(root)
    n.max_fringe_size = len(fringe)
    path_cost = {tuple(root.state): 0}

    # While the stack is not empty ...
    while fringe:

        # Pop node from stack
        node = fringe.pop()
        n.nodes_popped = n.nodes_popped + 1

        # Add popped node to visited
        visited.add(tuple(node.state))

        # If node - state matches the goal state ...
        # Return goal node - state and close output file
        if e.goal_test(node, goal_state):
            print('Goal state found')
            if dump_flag == 'true':
                f.close()
            return node

        # Expand node and generate children nodes, log number of nodes popped
        node.children = e.generate_next_states(node)
        n.nodes_expanded = n.nodes_expanded + 1

        # Log node details to output file
        if dump_flag == 'true':
            n.log_node_to_output(f, node, fringe, visited)

        # For each child node ...
        for next_node in node.children:

            # Make child node's parent equal to current node
            next_node.parent = node

            # If the next node has not been visited ...
            if tuple(next_node.state) not in visited:

                # Add node to fringe
                fringe.append(next_node)

                # Log maximum fringe size
                if len(fringe) > n.max_fringe_size:
                    n.max_fringe_size = len(fringe)

                # Update path, cumulative path, relative cost AND node depth
                n.update_path_costs(path_cost, next_node, node)
    return -1
