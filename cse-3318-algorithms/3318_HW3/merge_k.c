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


//Function Finds index of minimum value//
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
		nodePT temp = NULL; // (nodePT)malloc(sizeof(struct node)); //Do not need to allocate memory for temp because heap[p] already has memory allocated for it
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

//Function Builds a minimum heap//
void make_heap(int k, nodePT heap[])
{
	int p;
	for(p = (k-1)/2; p >= 0; p--)
	{
		sinkDown(heap, p, k);
	}
	
	printf("finished.\n The heap is:\n");
	for(int i = 0; i < k; i++)
	{
		print_list_pointer(heap[i]);
	}
	
}

//Function builds a minimum heap, but does not print "finished. The heap is: "//
void make_heap_NL(int k, nodePT heap[])
{
	int p;
	for(p = (k-1)/2; p >= 0; p--)
	{
		sinkDown(heap, p, k);
	}
}


//Function removes the minimum element of the Binary Tree//
nodePT remove_min(int* k, nodePT heap[])
{
	nodePT curr = heap[0];
	int i = *k-1;
	if (curr->next == NULL) 
	{
		heap[0] = heap[i];
		(*k) = (*k)-1;
		if (*k < 0) 
		{
			return NULL;
		}
		
		sinkDown(heap, 0, *k);
		
	} 
	else 
	{
		heap[0] = heap[0]->next;
		sinkDown(heap, 0, *k);
	}
	curr->next = NULL;
	return curr;
}


//Function merges k linked lists//
nodePT merge_k(int k, nodePT heap[], int debug)
{

	make_heap_NL(k, heap);
	nodePT first = remove_min(&k, heap);
	nodePT last = NULL;

	sinkDown(heap, 0, k);
	nodePT curr = first;
	
	//If debug is chosen...//
	if(debug == 1)
	{
		do
		{
			printf(" \n---------------- Sorted result list:\n");
			print_list_pointer(first);
			printf("\n ---- HEAP (start) -------- \n");
			for(int i = 0; i < k; i++)
			{
				print_list_pointer(heap[i]);
			}
			printf("\n ---- HEAP (end) -------- \n");
		
			//Tyh minimum element moves to the bottom of the tree and is removed//
			last = remove_min(&k, heap);
		
			//All elements in the heap have been removed//
			if (last == NULL) 
			{
				printf("Empty heap. no remove performed.\n");
				break;
			}
			
			curr->next = last;
			curr = last;
			
		} while (last!=NULL);
   
		return first; 
		
	}
	
	//If debug is not chosen...///
	else
	{
		do
		{
			//The minimum element moves to bottom of the tree and Sinkdown is perforemed//
			last = remove_min(&k, heap);
		
			//All elements in heap have been removed//
			if (last == NULL) 
			{
				printf("Empty heap. no remove performed.\n");
				break;
			}
			curr->next = last;
			curr = last;
		} while (last!=NULL);
		
		return first; 
	}
	
}

