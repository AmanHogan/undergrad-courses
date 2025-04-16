import sys
import random

# Constants ###############################################
RED = 0
BLUE = 1
COMPUTER = 'computer'
HUMAN = 'human'
# Initial command line arguments ##########################
num_red = None
num_blue = None
goes_first = COMPUTER

###############################################################
#   parse_command_line()
#   args - None
#   function - parses command line to get number of reds, 
#   blue, and who goes first
#   return - None
###############################################################

def parse_command_line():    
    
    global num_red, num_blue, goes_first
    try:
        num_red = int(sys.argv[1])
        num_blue = int(sys.argv[2])
        goes_first = sys.argv[3]

    # If an error occurs parsing the command line, 
    # assign a random integer
    except IndexError:
        num_red = random.randint(1, 10)
        num_blue = random.randint(1, 10)
        goes_first = 'computer'

###############################################################
#   utility(state)
#   args - takes in a terminal state
#   function - calculates the utility val of terminal state
#   return - returns utility of terminal state
###############################################################

def utility(state):
    red_score = state[RED] * 2
    blue_score = state[BLUE] * 3
    
    if state[RED] == 0 and state[BLUE] == 0:
        return 0
    elif state[RED] == 0:
        return -blue_score
    elif state[BLUE] == 0:
        return -red_score

###############################################################
#   terminal_test(state)
#   args - takes in a state
#   function - checks if either red pile or blue pile is empty
#   return - true if either pile is empty or
#   false if both piles are not empty
###############################################################

def terminal_test(state):
    if state[RED] == 0 or state[BLUE] == 0:
        return True
    else:
        return False 

###############################################################
#   succesors(state)
#   args - takes in a state
#   function - if there are marbles in the red pile, remove 
#   one marble from the red pile. Then if there are blue 
#   marbles in the pile, remove one blue marble from the pile
#
#   return - returns both a state with one less marble on 
#   first call, then returns a state with one less marble 
#   on second call, given the piles are not empty
###############################################################

def successors(state):
    if state[RED] > 0:
        yield ('red', (state[RED] - 1, state[BLUE]))
    if state[BLUE] > 0:
        yield ('blue', (state[RED], state[BLUE] - 1))

###############################################################
#   alpha_beta_decision(state)
#   args - takes in a state
#   function - performs alpha-beta search and returns the 
#   optimal action yielded from the search
#   return - an action, 'red' or 'blue'
###############################################################

def alpha_beta_decision(state):
    
    # Return the utility if terminal state
    if terminal_test(state):
        return utility(state)

    v = float('-inf')
    v_prime = None

    for action, successor in successors(state):
        
        # Compute the minimum value of the successor
        min_value_result = min_value(successor, v, float('inf'))

        # Update v and best_action if necessary
        if min_value_result > v:
            
            v = min_value_result
            v_prime = action

    return v_prime

###############################################################
#   max_value(state, alpha, beta)
#   args - state, alpha value, and beta value
#   function - finds the maximal utility value from the succesor 
#   states
#   return - utility value
###############################################################

def max_value(state, alpha, beta):

    # Return the utility if terminal state
    if terminal_test(state):
        return utility(state)
    
    # Find the maximum value from the MIN succesor, prune if neccessary
    v = float('-inf')
    for action, successor in successors(state):
        
        v = max(v, min_value(successor, alpha, beta))
        
        # prune
        if v >= beta:
            return v
        
        alpha = max(alpha, v)

    return v

###############################################################
#   min_value(state, alpha, beta)
#   args - state, alpha value, and beta value
#   function - finds the minimal utility value from 
#   the succesor states
#   return - utility value
###############################################################

def min_value(state, alpha, beta):
    
    # Return the utility if terminal state
    if terminal_test(state):
        return utility(state)
    
    # Find the minimum value from the MAX succesor, prune if neccessary
    v = float('inf')
    for action, successor in successors(state):
        v = min(v, max_value(successor, alpha, beta))
        
        # prune
        if v <= alpha:
            return v
        beta = min(beta, v)

    return v

###############################################################
#   start_game(state)
#   args - takes in initial red and blue marble count, and 
#   whoever is the first player
#   function - Alternates between computer and human. 
#   Each player plays plays a modified game of nim. If a 
#   player takes a marble and the count ends up to be 0, they win
#   return - None
###############################################################

def start_game(init_red, init_blue, first_player):

    # Set current player
    curr_player = first_player
    
    # Set initial state
    print(f"Starting Red: {init_red}, Starting Blue: {init_blue}, First Player: {first_player}")
    state = (init_red, init_blue)

    # Alternate turns between human and computer until game ends
    while not terminal_test(state):
        
        # If current player is a human, perform actions
        if curr_player == HUMAN:
            
            print(f"Current State: Reds: {state[RED]} Blues: {state[BLUE]}")
            
            # Get player input
            player_move = input("Your turn! Choose a pile (red/blue) to remove 1 marble from: ")
            while player_move != 'red' and player_move != 'blue':
                player_move = input("Invalid input. Choose red or blue...")
            
            # Remove from the red or blue pile and switch player
            if player_move == 'red':
                state = (state[RED] - 1, state[BLUE])
            else:
                state = (state[RED] , state[BLUE] - 1)
            if state[RED] > 0 and state[BLUE] > 0: 
                curr_player = COMPUTER

        # If the current player is a computer, perform alpha beta decision making
        else:
            print(f"Current State: Reds: {state[RED]} Blues: {state[BLUE]}")
            print("Computer's turn...")
            # Get computers action
            computer_move = alpha_beta_decision(state)
            print("Computer removed 1 marble from", computer_move)

            # Remove from the red or blue pile and switch player
            if computer_move == 'red':
                state = (state[RED] - 1, state[BLUE])
            else:
                state = (state[RED] , state[BLUE] - 1)
            
            if state[RED] > 0 and state[BLUE] > 0: 
                curr_player = HUMAN

    # Calculate final score and display winner
    print("Game over!")
    final_score = utility(state)
    
    if curr_player == HUMAN:
        print("Computer wins with a score of", abs(final_score))
    else:
        print("You win with a score of", abs(final_score))

        
# Driver code
parse_command_line()
start_game(num_red, num_blue, goes_first)