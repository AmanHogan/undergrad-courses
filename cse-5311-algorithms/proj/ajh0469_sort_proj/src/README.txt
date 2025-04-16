Name: Aman Hogan-Bailey
MavId: 1001830469
Date: 03/2023

Programming Language: 3.11.2 64 Python
Environement: VsCode and Microsoft CMD command line prompt

STRUCTURE ******************************************************************************************************************************************************************************
The driver code is specified in 'algo_main.py'. This python file is responsible for several functions related to sorting algorithms, as well as an AlgorithmData 
class that holds information about the data and the execution time of a sorting algorithm. This file calls the following python modules:

* algo_sorting.py - file contains several sorting algorithms implemented in Python.
    o	merge_sort(arr, data): 
    o	heap_sort(arr, data): This function implements the heap sort algorithm. 
    o	heapify(arr, n, i): This is a helper function for the heap_sort function.
    o	quick_sort(arr): This function implements the quick sort algorithm usininto two sub-arrays 
        around the pivot until the base case of an array with a single element is reached. 
    o	quick_sort_median(arr): partitions the array into three sub-arrays around the pivot, then recursively 
        sorts the left and right sub-arrays before concatenating them with the pivot sub-array.
    o	selection_sort(arr, data): This function finds the minimum element in the unsorted part of the array
        and swaps it with the first element of the unsorted part.
    o	insertion_sort(arr, data): This function implements the insertion sort algorithm
    o	bubble_sort(arr, data): This function implements the bubble sort algorithm.


* algo_main.py - This is a Python script that defines several functions related to sorting algorithms, as well as an AlgorithmData class that holds
     information about the data and the execution time of a sorting algorithm.
    o	choose_algorithm():  takes a string parameter choice that determines which sorting algorithm to run 
        on the global array variable, and updates the global algorithm_data variable with the execution time and sorted array. 
    o	create_array():  creates a random array of integers of length size, and updates the global array variable with the new array.
    o   compare_algorithms():   compares the results of the two most recent sorting algorithm runs stored in the global 
        list_of_sorted list, and prints the results to the console using the algo_gui.comparison_screen function.
    o	algo_graph():  displays a graph of the most recent sorting algorithm run using the algo_gui.graphing_screen function.

* algorthim_view.py (GUI)- module for a GUI application that allows the user to choose and compare sorting algorithms on randomly generated arrays of integers.
    o	The initialize_gui() function creates a main window for the GUI, where the user can input the desired size of 
        the array to be sorted and select a sorting algorithm using buttons. 
    o	The array_to_screen() function creates a new window to display the details of the selected sorting algorithm, 
        including the algorithm name, array size, start time, end time, run time, bytes per microsecond, and unsorted array.
    o	The module imports the tkinter module and uses its functions and widgets to create the GUI, as well as several functions from the
         algo_main module and algo_sorting module to perform the actual sorting. 

* algo_graph.py - This Python module is called "algo_graph.py".
    o	The purpose of the "graphing" function is to plot a graph of input sizes vs runtimes in microseconds.
    o	The function adds the graph_name to the graph_names list and prints a message indicating that it is graphing the specified algorithm. 

* inputs.txt
    o   Since, arrays are randomized using the random python module, no input are needed. This file is included to fit with the grading criterion.


* <sorting name>.png
    o   After graphing an algorithm, the program will save a png of the graph in the current running directory.

Program Logic **************************************************************************************************************************************************************************
1)  User is prompted to a screen that has a a variety of sorting algorithms (such as Merge Sort, Heap Sort, Quick Sort, etc.) to sort an array of random integers, and displays the results of each algorithm in real time.
2) The user must enter in the array size then press 'Submit'
3) The user then can interact with the program by choosing an algorithm to run, comparing the results of two algorithms, and graphing the run time of an algorithm.
4) The GUI will then show and display the details of the algorithm's  performance (start and end time, run time, number of bytes per microsecond, unsorted and sorted arrays) in a separate window.

HOW TO RUN ******************************************************************************************************************************************************************************
There are two ways to run this program:

Windows CMD:
Unzip the downloaded file.
Open your Windows terminal.
Make sure you have python version 3 or higher installed.
Locate the directory the source code where 'algo_main.py' is located: cd C:\Users\ .... \algo_main.py
Then, from the command-line run: 'python algo_main.py'
The code should then output the reults

Vscode:
Unzip the downloaded file.
Open the folder in vscode and select 'trust this folder'
Set up your vscode to have a python Environement
    * Hold down SHIFT+CTRL+P and select 'Python:select interpter' and choose the path where python is installed on your system
Find the 'red_blue_nim.py' and right click and select 'Run python file in terminal'
    * This will open a terminal in Vscode using a python interpreter.
Now, with the terminal open, enter 'python algo_main.py'
The program should then run and print the neccessary outputs


