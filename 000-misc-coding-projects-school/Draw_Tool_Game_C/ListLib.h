//Aman Hogan-Bailey MAV-ID: 1001830469//
//Coding Assignment 7//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _LIST_LIB_H
#define _LIST_LIB_H

typedef struct node
{
	char Letter;
	char *DrawCommand;
	struct node *next_ptr;
}
NODE;

void AddDrawCommandToList(char, char DC[], NODE**);
NODE *FindLetter(NODE *LinkedListHead, char Letter, char DC[]);

#endif
