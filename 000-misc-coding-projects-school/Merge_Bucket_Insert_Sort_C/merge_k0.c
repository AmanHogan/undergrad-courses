#include <stdlib.h>
#include <stdio.h>

#include "merge_k.h"  // includes list.h

//Sorts linked list L in pace using insertion sort//
nodePT sort_list(nodePT L){
	
	//Initializing temps and current//
	struct node *currentNode = L, *marker = NULL;
	int temp;
	
	//If the head is NULL, return//
	if(L == NULL)
	{
		return L;
	}
	
	//If head is not NULL, traverse the list//
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
	return L;
}


/* It is recommended to implement a sinkDown function in this file. 
You can declare its header at the top of this file (after include) 
write the implementation anywhere in this file. 
(You cannot modify any of the list.h or merge_k.h files) 
*/
int idxOfMinValue(nodePT heap[], int p, int left, int right, int k)
{
	//p = parrent node, imv = smallest value, parrent node = smallest value//
	int imv = p; 
	
	// If there is a left child AND is bigger than the parent...
	if ((left < k) && (((heap[left])->data) < ((heap[imv])->data)))
	{
		imv = left; //set imv(smallest value) to index of left child
	
	}
	
	// If there is a right child AND it is bigger than max value seen ...
	if ((right < k) && ((heap[right]) != NULL) &&(((heap[right])->data) < ((heap[imv])->data) ))
	{
		imv = right; // set imv to index of left child
	}
	
	return imv;
}


void sinkDown(nodePT heap[], int p, int k)
{
	//declaring variables//
	int left, right, imv;
	
	//initializing left and right child//
	left = (2*p) +1;
	right = (2*p) + 2;
	
	//Find smallest Value//
	imv = idxOfMinValue(heap, p, left, right, k);
	
	//While smallest value is not the parent and is lessthan/equal to k...//
	while( (imv != p) && (imv <= k) )
	{
		//SWAP heap[imv] <-> heap[p]//
		nodePT temp = (nodePT)malloc(sizeof(struct node));
		temp = heap[p];
		heap[p] = heap[imv];
		heap[imv] = temp;
		
		//parent is the smallest value//
		p = imv;
		
		//find left and right again//
		left = (2*p) +1;
		right = (2*p) + 2;
		
		//find smallest value//
		imv = idxOfMinValue(heap, p, left, right,k);
	}
	
}


/* Turns the given array (named heap) into an actual Min-Heap
   using the bottom-up method to build the heap. 
   (See buidMaxHeap pseudocode in slides)
*/
void make_heap(int k, nodePT heap[])
{
	int p;
	for(p = (k-1)/2; p >= 0; p--)
	{
		sinkDown(heap, p, k);
	}
}


/*  heap is a Min-Heap of linked lists
	remove_min will remove AND RETURN the first node of the list at index 0.
	k (size of heap) will only change when that removal leaves that list empty.
*/
nodePT remove_min(int* k, nodePT heap[])
{
	//TODO
	return NULL;
}


/*
Input
   heap - is a Min-Heap array of SORTED single linked lists. 
   k - size of array heap. The first item is at index 0
   debug - debug on/off:
			if debug is 1, student code should print debugging information as well: heap and sorted result list
			if debug is 0, it does not print debugging infomation. 
			if debug is anything but 1, it does not print debugging infomation.
Returns: a sorted single linked list built by merging the k lists.

Algorithm
   Merging process: 
	- use the heap to identify and remove the node, np, with the smallest data out 
      of the k lists.
	- insert np at the end of result list.
	
*/
nodePT merge_k(int k, nodePT heap[], int debug)
{
	//TODO///
	///////////Personal Debug check - Remove when finished////////
	printf("\nThe Binary MinHeap is:\n");
	for(int i = 0; i < k; i++)
	{
		printf("Index[%d] storing %d\n", i, (heap[i])->data);
	}
	
	////////////////////////////////////////////////////////////
   return NULL; // place holder code
}
