
# Author: Aman Hogan-Bailey
# MavID: 1001830469
# Date: 03/2023

# file contains several sorting algorithms implemented in Python.

#############################################################################################################
#
# merge_sort(arr, data): his function implements the merge sort algorithm. 
#
# heap_sort(arr, data): This function implements the heap sort algorithm. 
#
# heapify(arr, n, i): This is a helper function for the heap_sort function.
#
# quick_sort(arr): This function implements the quick sort algorithm usininto two sub-arrays 
#   around the pivot until the base case of an array with a single element is reached. 
#
# quick_sort_median(arr): partitions the array into three sub-arrays around the pivot, then recursively 
#   sorts the left and right sub-arrays before concatenating them with the pivot sub-array.
#
# selection_sort(arr, data): This function finds the minimum element in the unsorted part of the array
#   and swaps it with the first element of the unsorted part.
#
# insertion_sort(arr, data): This function implements the insertion sort algorithm
#
# bubble_sort(arr, data): This function implements the bubble sort algorithm.
#
############################################################################################################


def merge_sort(arr, data):
    
    # If the array is greater than 1, partition, then merge
    if len(arr) > 1:

        # Divide the array into two halves
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        # Recursively call merge_sort to sort each half
        merge_sort(left_half, data)
        merge_sort(right_half,data)

        # Merge the two sorted halves
        # Merge the partitions
        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            
            if left_half[i] < right_half[j]:
                
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            
            arr[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1
            
    data.log_algorithm_data(arr, 'MERGE')


def heap_sort(arr, data):

    n = len(arr)

    # Build a max heap from the array
    for i in range(n // 2 - 1, -1, -1):    
        heapify(arr, n, i)

    # Extract elements one by one from the heap
    for i in range(n - 1, 0, -1):
        
        # Move current root to end
        arr[i], arr[0] = arr[0], arr[i]
        
        # Call max heapify on the reduced heap
        heapify(arr, i, 0)

    data.log_algorithm_data(arr, 'HEAP')


def heapify(arr, n, i):
    # Find largest among root and two children
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left] > arr[largest]:
        largest = left
    if right < n and arr[right] > arr[largest]:
        largest = right
    # If largest is not root
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        
        # Recursively heapify the affected sub-tree
        heapify(arr, n, largest)


def quick_sort(arr):

    if len(arr) <= 1:
        return arr

    pivot = arr[0]
    left = []
    right = []

    for i in range(1, len(arr)):

        if arr[i] < pivot:
            left.append(arr[i])

        else:
            right.append(arr[i])

    return quick_sort(left) + [pivot] + quick_sort(right)

def quick_sort_median(arr):
    
    if len(arr) <= 1:
        return arr
    
    # Select pivot as median of first, middle, and last elements
    first = arr[0]
    middle = arr[len(arr) // 2]
    last = arr[-1]
    pivot = sorted([first, middle, last])[1]

    # Partition array into sub-lists
    left = []
    right = []
    pivots = []

    for i in range(len(arr)):
        
        if arr[i] < pivot:
            left.append(arr[i])
        
        elif arr[i] > pivot:
            right.append(arr[i])
        
        else:
            pivots.append(arr[i])

    # Recursively sort sub-lists
    left_sorted = quick_sort_median(left)
    right_sorted = quick_sort_median(right)

    # Concatenate sorted sub-lists with pivot values
    return left_sorted + pivots + right_sorted

def selection_sort(arr, data):

    for i in range(len(arr)):

        min_index = i

        for j in range(i+1, len(arr)):
            
            if arr[j] < arr[min_index]:
                min_index = j

        arr[i], arr[min_index] = arr[min_index], arr[i]

    data.log_algorithm_data(arr, 'SELECTION')

def insertion_sort(arr, data):

    for i in range(1, len(arr)):

        key = arr[i]
        j = i - 1

        while j >= 0 and key < arr[j]:

            arr[j + 1] = arr[j]
            j = j - 1

        arr[j + 1] = key

    data.log_algorithm_data(arr, 'INSERTION')
   
def bubble_sort(arr, data):

    n = len(arr)

    for i in range(n):

        # Last i elements are already sorted
        for j in range(0, n-i-1):
           
            # Traverse the array from 0 to n-i-1
            # Swap if the element found is greater than the next element
            if arr[j] > arr[j+1] :
                arr[j], arr[j+1] = arr[j+1], arr[j]
    
    data.log_algorithm_data(arr, 'BUBBLE')
