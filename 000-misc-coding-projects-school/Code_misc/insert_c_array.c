#include <stdio.h>
#include <stdlib.h>

// Function sorts an Integer array using Insertion Sort Algorithm
// from least to greatest
void insertion_sort(int list[], int N);

// Function prints to the console an integer array
void print_array(int list[], int N);

int main()
{
	/* 
		Initializing an integer array
		Storing the number of elements of array by 
		diving the total bytes of the array by the
		bytes of a single element 
	*/
   int arr[] = {3, 5, 1, 1, 4, 12, 7, 9};
   int N = sizeof(arr) / sizeof(arr[0]);
	
	// Printing starting array, sorting array, printing final array
   print_array(arr, N);
   insertion_sort(arr, N);
   print_array(arr, N);
	
}

void insertion_sort(int list[], int N)
{
   int key, i, j, temp;
	
	// For each element in array...
   for(i = 0; i < N; i++)
   {
		// Storing the current value of array into "key"
      key = list[i];
      
		// Getting previous index
		j = i-1;
      
		// While the previous index is not 0, and the previous value
		// is greater than the current value, then swap those elements
      while((j >= 0) && (list[j] > key))
      {
			// Swap the current element and the previous element
         temp = list[j];
         list[j] = list[j+1];
         list[j+1] = temp;
         
			// Continue to swap the sorted list elements until the index is '0'
         j--;
      }
   }
}

void print_array(int list[], int N)
{
   int i;
   
	// For each element in the array, print it to the console
   printf("Array Elements: [ ");
   for(i = 0; i < N; i++)
   {
       printf("%d, ", list[i]);
   }
   printf("]\n");
}
