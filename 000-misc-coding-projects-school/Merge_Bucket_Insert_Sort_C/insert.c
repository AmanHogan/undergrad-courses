#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[], int N);
void print_array(int arr1[], int X);
int main()
{
	int array[7] = {1, 34, 12, 5, 11, 0, 4};
	int n = 7;
	
	printf("Your intital array is: ");
	print_array(array, n);
	insertion_sort(array, n);
	printf("\n\nYour sorted array is: ");
	print_array(array, n);
	printf("\n\n");

}

void print_array(int arr1[] , int X)
{
	for(int j = 0; j < X; j++)
	{
		printf("%3d,", arr1[j]);
	}
}


void insertion_sort(int arr[], int N)
{
	int i, k, key;
	
	for(i = 1; i < N; i++)
	{
		key = arr[i];
		
		k = i - 1;
		
		while(k >= 0 && arr[k] > key)
		{
			arr[k + 1] = arr[k];
			
			k = k - 1;
		}
		
		arr[k+1] = key; 
		
		
	}


}

