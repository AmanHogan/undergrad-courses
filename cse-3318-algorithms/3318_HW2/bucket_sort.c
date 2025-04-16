/* 
 * Aman Hogan-Bailey
 * 1001830469
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "list.h"

//intitializing helper functions//
void print_array(int arr[], int N);
void open_file (int N, int arr[]);
void findMaxMin(int *maximum, int *minimum, int index, int array[]);
void InsertionSort(nodePT LinkedListhead);
void list_2_array(struct node *my_list, int Array[], int *counter);
nodePT array_to_list(int array[], int n);


//calling run1()//
void run1()
{
	//initializing initial Values
	int N;
	char filename[100];
	
	//Opening file and retrieveing file name
	FILE *fp;
	printf("\nPlease enter the filename: ");
	scanf("%s", filename);
	fp = fopen(filename, "r");
	
	//If File cannont be opened, return//
	if(fp == NULL)
	{
		printf("File could not be opened.\n");
		return;
	}
	
	//Reading File data//
	fscanf(fp, "%d", &N);//storing N
	
	
	int arr[N];
	for(int i = 0; i < N; i++)
	{
		fscanf(fp, "%d", &(arr[i]));//storing elements
	}
	fclose(fp);
	
	
	//printing the array data to console
	printf("\n array:");
	for(int i = 0; i < N; i++)
	{
		printf("%5d,", arr[i]);
	}
	
	//function retrieves maximum and minimum
	int min = arr[0];
	int max = 0;
	findMaxMin(&max, &min, N, arr);
	
	
	printf("\n\nBucketsort : min=%d, max=%d, N=%d buckets", min, max, N);
	//setting number of buckets equal to N//
	int NB = N;
	
	
	//Initializing Linked List array of Buckets and setting intial values to 0//
	nodePT Buckets[NB];
	for(int j = 0; j < NB; j++)
	{
		Buckets[j] = NULL;
	}
	
	
	//Sorting values into buckets//
	for(int i = 0; i < N; i++)
	{
		double index = (((arr[i] - (double)min)*NB)/(1+(double)max-(double)min));
		
		printf("\narr[%d]= %4d, idx = %d", i, arr[i], (int)index);//printing to console
		if(Buckets[(int)index] != NULL)
		{
			struct node *newnode = new_node(arr[i]);
			insert_node_after(Buckets[(int)index], newnode);
		}
		
		else
		{
			Buckets[(int)index] = new_node(arr[i]);
		}
	}
	
	//Using insertion sort on Bucket List//
	for(int i = 0; i < NB; i++)
	{
		InsertionSort(Buckets[i]);
	}
	
	//Initializing array and setting values to 0//
	int array[NB];
	for(int i = 0; i < NB; i++)
	{
		array[i] = 0;
	}
	
	//Converting Sorted List into Array//
	int j = 0;
	for(int i = 0; i < NB; i++)
	{
		if (Buckets[i] != NULL)
		{
			struct node *curr = Buckets[i];
			while(curr != NULL)
			{
				array[j] = curr->data;
				curr = curr->next;
				j++;
			}
		}
	}
	
	printf("\n");
	for(int i = 0; i < NB; i++)
	{
		printf("------ List at index %d :", i);
		print_list_horiz(Buckets[i]);
	}
	
	for(int i = 0; i < NB; i++)
	{
		destroy_list(Buckets[i]);
	}
	
	
	printf("\n array:");
	for(int i = 0; i < NB; i++)
	{
		printf("%5d,", array[i]);
		
		
	}
	printf("\n");
}


//Calling function tht sorts the Buckets[] array//
void InsertionSort(nodePT LinkedListhead)
{
	//Initializing variables//
	struct node *currentNode = LinkedListhead, *marker = NULL;
	int temp;
	
	//If the head is NULL, return//
	if(LinkedListhead == NULL)
	{
		return;
	}
	
	else
	{
		while(currentNode != NULL)
		{
			marker = currentNode->next;
			while(marker != NULL)
			{
				//Insertion Sort
				if(currentNode->data > marker->data)
				{  
					temp = currentNode->data;
					currentNode->data = marker->data;
					marker->data = temp;
				}
				marker = marker->next;  
			}
			currentNode = currentNode->next;  
		}
	}
}


//Converts an Array to a List
nodePT array_to_list(int array[], int n)
{
	//Intitializing variables//
	int j;
	nodePT lastP = NULL;
	nodePT newP = NULL;
	nodePT L = (nodePT)malloc(sizeof(struct node));
	
	L->data = array[0];
	L->next = NULL;
	lastP = L;
	
	for(j = 1; j < n; j++)
	{
		newP = (nodePT)malloc(sizeof(struct node));
		newP->data = array[j];
		newP->next = NULL;
		lastP->next = newP;
		lastP = newP;
	}
	return L;
}


//Function Finds the Maximum and Minimum of an Array
void findMaxMin(int *maximum, int *minimum, int index, int array[])
{
	for(int i = 0; i < index; i++)
	{
		//Finding the Maximum
		if(*maximum < array[i])
		{
			*maximum = array[i];
		}
		
		//Finding the minimum
		if(*minimum > array[i])
		{
			*minimum = array[i];
		}
	}
}

//Function printsa array to console
void print_array(int arr[], int N){
	
	int j;
	
	printf("\n array: ");
	
	for(j= 0; j<N; j++)
	{
		printf("%5d,", arr[j]);
	}
	
	printf("\n");
}


int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		scanf("%d",&option);
	} while (option == 1);

   return 0;
}