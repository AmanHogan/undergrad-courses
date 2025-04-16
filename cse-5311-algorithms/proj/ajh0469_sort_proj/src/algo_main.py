import sys
import random
import time
import algo_sorting
import algo_gui
import copy


# Author: Aman Hogan-Bailey
# MavID: 1001830469
# Date: 03/2023

# GLOBALS ####################
array = []
algorithm_data = None
n = None
list_of_sorted = []
unsorted = []
#############################

class AlgorithmData:
    
    def __init__(self, array, data_size, start_time):
        self.data_size = data_size
        self.unsorted = array
        self.start_time = start_time 
        self.end_time = 0
        self.run_time = 0
        self.data_per_sec = 0
        self.sorted = []
        self.algorithm_name = 'NULL'
    
    def log_algorithm_data(self, array, algo_name):
        self.end_time = time.perf_counter_ns() / 1000
        self.run_time = self.end_time - self.start_time
        self.data_per_sec = self.data_size * 4/(self.run_time)
        self.sorted = array
        self.algorithm_name = algo_name



############################################################################
# Args:
#   choice - string containing one of clicked gui choices on-screen
#  
# Function:
#   Takes the string name of a sorting algorithm or onscreen choice and chooses an 
#   algorithm to run based on this choice. Algroithm is run and data about its
#   runtime is stored an an AlgorithmData object
#
# Returns:
#   None
############################################################################
def choose_algorithm(choice):

    global algorithm_data, array, list_of_sorted
    algorithm_data = AlgorithmData(unsorted, n, time.perf_counter_ns() /1000)
    print(f"Unsorted Array: {unsorted}")

    if  n == None and choice != 'EXIT':
        print('Array size not entered. Enter array size and press \'Submit\'')
        return

    if choice == 'EXIT':
        exit(0)
    
    # Choose algorithm
    elif choice == 'MERGE':
        
        algo_sorting.merge_sort(array, algorithm_data)
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)

    elif choice == 'HEAP':
        algo_sorting.heap_sort(array, algorithm_data)
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)

    elif choice == 'QUICK':
        
        array = algo_sorting.quick_sort(array)
        algorithm_data.log_algorithm_data(array, 'QUICK')
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)

    elif choice == 'QUICK3':
        array = algo_sorting.quick_sort_median(array)
        algorithm_data.log_algorithm_data(array, 'QUICK3')
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)

    elif choice == 'INSERTION':
        algo_sorting.insertion_sort(array, algorithm_data)
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)
        
    elif choice == 'SELECTION':
        algo_sorting.selection_sort(array, algorithm_data)
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)
        
    elif choice == 'BUBBLE':
        algo_sorting.bubble_sort(array, algorithm_data)
        algo_gui.array_to_screen(algorithm_data)
        list_of_sorted.append(algorithm_data)

############################################################################
# Args:
#   size - integer input size
#  
# Function:
#   creates an array of the input size using random integers from 1 to 100
#
# Returns:
#   None
############################################################################
def create_array(size):
    global array, n, unsorted
    arr = []
    n = size
    arr = [random.randint(1, 100) for i in range(size)]
    array = copy.deepcopy(arr)
    unsorted = copy.deepcopy(array)


############################################################################
# Args:
#   None
#  
# Function:
#   Calls a function that compares the last two sorting algorithms that were
#   run
#
# Returns:
#   None
############################################################################
def compare_algorithms():
    global list_of_sorted

    if len(list_of_sorted) < 2:
        print("At least two algortihms must have been run in order to compare two algorithms.")
        return

    cur_index = len(list_of_sorted) - 1
    prev_index = cur_index - 1
    algo_gui.comparison_screen(list_of_sorted[prev_index], list_of_sorted[cur_index])


############################################################################
# Args:
#   None
#  
# Function:
#   calls a function that graphs the type of most recent algorithm run 
#
# Returns:
#   None
############################################################################
def graph_algorithms():
    global list_of_sorted

    if len(list_of_sorted) < 1:
        print("At least one algortihm must have been run in order to graph.")
        return
    
    sorting_algorithm = list_of_sorted[len(list_of_sorted)-1].algorithm_name
    algo_gui.graphing_screen(sorting_algorithm)


if __name__ == '__main__':
    algo_gui.initialize_gui()

