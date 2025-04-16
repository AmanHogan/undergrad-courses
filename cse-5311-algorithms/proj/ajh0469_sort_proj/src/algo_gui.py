import tkinter as tk
import algo_main
import algo_sorting
import algo_graph
import time

# Author: Aman Hogan-Bailey
# MavID: 1001830469
# Date: 03/2023

algo_count = 0
algo_window = None
entry_field = None


############################################################################
# Args:
#   None
#  
# Function:
#   Initializes a gui grid of sorting algorihtm choices and functions you can
#   perform on them, and an exit button
#
# Returns:
#   None
############################################################################

def initialize_gui():

    global entry_field

    # create the main window
    root = tk.Tk()
    root.title("Sorting Algorithms")

    # create the entry field and label
    entry_label = tk.Label(root, text="Enter array size:", width=15, height=3)
    entry_field = tk.Entry(root, width=15)
    entry_button = tk.Button(root, text="Submit", height=3, width=15, command=lambda: onSubmit())

    # create the buttons
    button_merge = tk.Button(root, text="Merge Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('MERGE'))
    button_heap = tk.Button(root, text="Heap Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('HEAP'))
    button_quick = tk.Button(root, text="Quick Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('QUICK'))
    button_quick3 = tk.Button(root, text="Quick Median Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('QUICK3'))
    button_insertion = tk.Button(root, text="Insertion Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('INSERTION'))
    button_selection = tk.Button(root, text="Selection Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('SELECTION'))
    button_bubble = tk.Button(root, text="Bubble Sort", height=3, width=15, command=lambda: algo_main.choose_algorithm('BUBBLE'))
    button_exit = tk.Button(root, text="Exit Program", height=3, width=15, command=lambda: algo_main.choose_algorithm('EXIT'))
    button_compare = tk.Button(root, text="Compare Recent", height=3, width=15, command=lambda: algo_main.compare_algorithms())
    button_graph = tk.Button(root, text="Graph Recent", height=3, width=50, command=lambda: algo_main.graph_algorithms())

    # layout the buttons using the grid geometry manager
    entry_label.grid(row=0, column=0)
    entry_field.grid(row=0, column=1)
    entry_button.grid(row=0, column=2)

    button_merge.grid(row=1, column=0)
    button_heap.grid(row=1, column=1)
    button_quick.grid(row=1, column=2)
    button_quick3.grid(row=2, column=0)
    button_insertion.grid(row=2, column=1)
    button_selection.grid(row=2, column=2)
    button_bubble.grid(row=3, column=0)
    button_exit.grid(row=3, column=1)
    button_compare.grid(row=3, column=2)
    button_graph.grid(row=4, column=0, columnspan=3)


    # start the main event loop
    root.mainloop()


############################################################################
# Args:
#   None
#  
# Function:
#   Sends the input size the user entered to a function that will create 
#   an array of that size.
#
# Returns:
#   None
############################################################################
def onSubmit():
    global entry_field
    array_entry_size = int(entry_field.get())
    print("Size of the Array: ",array_entry_size)
    algo_main.create_array(array_entry_size)
    

############################################################################
# Args:
#   data - an object that has runtime details of the algorithm
#  
# Function:
#   Logs the data of the algorithm to the scren using gui components
#
# Returns:
#   None
############################################################################
def array_to_screen(data):
    
    global algo_count, algo_window
    algo_window = tk.Tk()
    algo_window.title("Algorithm Details")

    name_label = tk.Button(algo_window, text= f"Algorithm: #{str(algo_count)} ({data.algorithm_name})" , height=2, width=200, anchor="w",  command=lambda: log_data_to_terminal(data.algorithm_name))
    name_label.grid(row=0, column=0)

    size_label = tk.Button(algo_window, text=f"Array Size: {str(data.data_size)} integers", width=200, height=2, anchor="w",  command=lambda: log_data_to_terminal(data.data_size))
    size_label.grid(row=1, column=0)

    start_label = tk.Button(algo_window, text=f"Start Time: {str(round(data.start_time))} (CPU Clock Time)",width=200,  height=2, anchor="w",  command=lambda: log_data_to_terminal(data.start_time))
    start_label.grid(row=2, column=0)

    end_label = tk.Button(algo_window, text=f"End Time: {str(round(data.end_time))} (CPU Clock Time)", width=200,  height=2, anchor="w",  command=lambda: log_data_to_terminal(data.end_time))
    end_label.grid(row=3, column=0)

    run_label = tk.Button(algo_window, text=f"Run Time: {str(round(data.run_time, 4))} (micro-seconds)", width=200,  height=2, anchor="w",  command=lambda: log_data_to_terminal(data.run_time))
    run_label.grid(row=4, column=0)

    data_sec_label = tk.Button(algo_window,text=f"Bytes per microsecond: {str(round(data.data_per_sec, 4))}", width=200, height=2, anchor="w",  command=lambda: log_data_to_terminal(data.data_per_sec))
    data_sec_label.grid(row=5, column=0)

    unsorted_label = tk.Button(algo_window, text=f"Unsorted Array: {str(data.unsorted)} ", width=200,  height=2, anchor="w",  command=lambda: log_data_to_terminal(data.unsorted))
    unsorted_label.grid(row=6, column=0)

    sorted_label = tk.Button(algo_window, text=f"Sorted Array: {str(data.sorted)}" , width=200, height=2, anchor="w",  command=lambda: log_data_to_terminal(data.sorted))
    sorted_label.grid(row=7, column=0)
   
    algo_count = algo_count + 1


############################################################################
# Args:
#   algo1 -  an object that has runtime details of the algorithm
#   algo2 - an object that has runtime details of the algorithm
#  
# Function:
#   Logs comparrsion details of the two algorithm datas sent to the object
#
# Returns:
#   None
############################################################################
def comparison_screen(algo1, algo2):
    global algo_count

    comparrsion_window = tk.Tk()
    comparrsion_window.title("Comparison Window:")


    algo1__name = f"Algorithm: #{str(algo_count-2)} ({algo1.algorithm_name})"
    algo2_name =  f"Algorithm: #{str(algo_count-1)} ({algo2.algorithm_name})"
    
    run_time_difference = str(round(abs(algo1.run_time - algo2.run_time), 4))
    data_per_micro = str(round(abs(algo1.data_per_sec - algo2.data_per_sec), 4))


    vs_label = tk.Label(comparrsion_window, text= f"{algo1__name} vs {algo2_name}" , width=200,  height=2, anchor="w")
    run_label = tk.Label(comparrsion_window, text= f"Run Time Difference: {run_time_difference} micro-seconds", width=200,  height=2, anchor="w")
    data_per_label = tk.Label(comparrsion_window, text=f"Bytes per microsecond {data_per_micro}", width=200,  height=2, anchor="w")
 

    vs_label.grid(row=0, column=0)
    run_label.grid(row=1, column=0)
    data_per_label.grid(row=2, column=0)



############################################################################
# Args:
#   choice - string version of the algrithm to be graphed
#  
# Function:
#   graphs the algorithm from array sizes 10 to 100 using the algorithm choice
#
# Returns:
#   None
############################################################################
def graphing_screen(choice):

    run_times = []
    array_sizes = []

    for i in range(10, 101, 10):

        algo_main.create_array(i)
        algo = algo_main.AlgorithmData(algo_main.unsorted, algo_main.n, time.perf_counter_ns() /1000)

        if choice == 'MERGE':
            algo_sorting.merge_sort(algo_main.array, algo)

        elif choice == 'HEAP':
            algo_sorting.heap_sort(algo_main.array, algo)

        elif choice == 'QUICK':
            array = algo_sorting.quick_sort(algo_main.array)
            algo.log_algorithm_data(algo_main.array, 'QUICK')

        elif choice == 'QUICK3':
            array = algo_sorting.quick_sort_median(algo_main.array)
            algo.log_algorithm_data(algo_main.array, 'QUICK3')

        elif choice == 'INSERTION':
            algo_sorting.insertion_sort(algo_main.array, algo)
            
        elif choice == 'SELECTION':
            algo_sorting.selection_sort(algo_main.array, algo)
            
        elif choice == 'BUBBLE':
            algo_sorting.bubble_sort(algo_main.array, algo)
        
        array_sizes.append(i)
        run_times.append(round(algo.run_time,2))

    algo_graph.graphing(array_sizes, run_times, choice.lower())
    print(f'X values: {array_sizes}\nY values: {run_times}')


# Logs the unrounded data to terminal on a clicked gui component
def log_data_to_terminal(data):
    print(data)