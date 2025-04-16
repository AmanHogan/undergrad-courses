#include <stdio.h>
#include <stdlib.h>



typedef struct node *nodePT;
struct node //A node is a self referential structure
{
	int data;
	struct node *next;

};

nodePT array_2_list(int array[], int N);




int main(void)
{
	int arr[5] = {21, 5, 36, 89, 12};
	
	if((prev == NULL) || (prev->next == NULL) || (prev->next->next == NULL))
	{
		return;
	}
	
	
	nodePT A = prev->next;
	nodePT B = prev->next->next;
	nodePT C = B->next;
	
	
	prev->next = B;
	A->next = C;
	B->next = B;
	
	
	
	
	
	
	
	
	
	
	


}

nodePT array_2_list(int array[], int N)
{
	nodePT newP = NULL;
	nodePT lastP = NULL;
	
	nodePT LLH = (nodePT)malloc(sizeof(node struct));
	
	LLH->data = array[0];
	LLH->next = NULL;
	
	lastP = LLH;
	
	for(int i = 1; i < N; i++)
	{
		newP = (nodePT)malloc(sizeof(strcut node));
		
		newP->data = array[i];
		newP->next = NULL;
		
		lastP->next = newP;
		lastP = newP;
		
	}
	
	return LLH;
}


void swap_2_after(nodePT prev)
{
	//if there are not enough nodes or the node sent to function is NULL//
	if((prev == NULL) || (prev->next == NULL) || (prev->next->next == NULL))
	{
		return;
	}
	
	nodePT A = prev->next;
	nodePT B = prev->next->next;
	nodePT C = B->next;
	
	prev->next = B;
	A->next = C;
	B->next = A;
	
	
	
	
	
	
	
	
	
	
	
	
}