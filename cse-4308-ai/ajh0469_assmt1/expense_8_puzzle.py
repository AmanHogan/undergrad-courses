import file2puzzle as f2p
import breadth as b
import depth as d
import uniform as u
import greedy as g
import nodes as n
import a_star as a
import depth_limited as dl
import iterative_deep as i
import sys

start_file, goal_file, method, dump_flag, depth_limit, init_state, goal_state  = None, None, None, 'false', None, None, None


if 4 > len(sys.argv) >= 1:
    print(f'Missing Command Line arguments: Args: \n{sys.argv}')
    exit(-1)

try:
    start_file = sys.argv[1]
    goal_file = sys.argv[2]
    method = sys.argv[3]
    dump_flag = sys.argv[4]
    depth_limit = sys.argv[5]

except IndexError as MissingArgs:
    pass

init_state = f2p.create_puzzle(start_file)
goal_state = f2p.create_puzzle(goal_file)

# Breadth First Search
if method == 'bfs':
    
    goal_node = b.bfs(init_state, goal_state, sys.argv, dump_flag)
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)
    n.find_goal_path(goal_node)
    n.print_path_details()

# Depth First Search
elif method == 'dfs':
    
    goal_node = d.dfs(init_state, goal_state, sys.argv, dump_flag)
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)

    n.find_goal_path(goal_node)
    n.print_path_details_dfs()
    print('Printed dfs() solution output into dfs.txt')

# Uniform Cost Search
elif method == 'ucs':
    
    goal_node = u.ucs(init_state, goal_state, sys.argv, dump_flag)
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)
    n.find_goal_path(goal_node)
    n.print_path_details()

# Greedy Search
elif method == 'greedy':
    
    goal_node = g.greedy(init_state, goal_state, sys.argv, dump_flag)
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)
    n.find_goal_path(goal_node)
    n.print_path_details()

 # A * Search
elif method == 'a*':
   
    goal_node = a.a_s(init_state, goal_state, sys.argv, dump_flag)
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)
    n.find_goal_path(goal_node)
    n.print_path_details()

# Depth-Limited Search
elif method == 'dls':
    if depth_limit == None:
        depth_limit = int(dump_flag)
        
    goal_node = dl.dls(init_state, goal_state, sys.argv, dump_flag, int(depth_limit))
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)
    n.find_goal_path(goal_node)
    n.print_path_details()

# Iterative Deepining Search
elif method == 'ids':
    if depth_limit == None:
        depth_limit = int(dump_flag)
    try:    
        max_depth = int(depth_limit)
    except TypeError as e:
        print('A MAX DEPTH needs to be specified for iterative deepining search implementation. Exiting...')
        exit(0)        
    goal_node = i.ids(init_state, goal_state, sys.argv, dump_flag, max_depth)
    if goal_node == -1:
        print('No solution was found or at some point the fringe became empty')
        exit(0)
    n.find_goal_path(goal_node)
    n.print_path_details()
  



