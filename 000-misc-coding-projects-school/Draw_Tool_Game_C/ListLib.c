//Aman Hogan-Bailey MAV-ID: 1001830469//
//Coding Assignment 7//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListLib.h"
#include "FileLib.h"
#include "DrawTool.h"

void AddDrawCommandToList(char Letter, char DC[], NODE** LinkedListHead)
{
	/* declare pointers of type NODE named TempPtr and NewNode */
	NODE *TempPtr, *NewNode;
	
	/* mallocing() NewNode and assigning it to the Letter passed into function*/
	NewNode = malloc(sizeof(NODE));
	NewNode->Letter = Letter;
	
	//mallocing() DrawCommand, then copying DC into DrawCommand//
	NewNode->DrawCommand = malloc(strlen(DC) * sizeof(char)+1);
	strcpy(NewNode->DrawCommand, DC);
	
	//setting the nextptr to NULL//
	NewNode->next_ptr = NULL;
	
	/* If the LinkedListHead is NULL, then give it the address of the new node */
	if(*LinkedListHead == NULL)
	{
		*LinkedListHead = NewNode;
	}
	
	/* Else traverse to the end of the linked list and add the new node */
	else
	{
		TempPtr = *LinkedListHead;
		
		while(TempPtr->next_ptr != NULL)
		{
			TempPtr = TempPtr->next_ptr;
		}
		
		TempPtr->next_ptr = NewNode;
	}
}

NODE *FindLetter(NODE *TempPtr, char Letter, char DC[])
{
	/* while traversing the linked list AND the Letter in the node is not the Letter passed in */
	while((TempPtr != NULL )&& (TempPtr->Letter != Letter))
	{
		/* move TempPtr */
		TempPtr = TempPtr->next_ptr;
	}
	
	if (TempPtr != NULL)
	{
		/* copy the DrawCommand from the node into the passed in parameter */
		strcpy(DC, TempPtr->DrawCommand);
		
		/* return the next pointer stored in TempPtr */
		return TempPtr->next_ptr;
	}
	
	/* return TempPtr */
	return TempPtr;
}
