//Aman Hogan-Bailey MAV-ID: 1001830469//
//Coding Assignment 7//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileLib.h"
#include "ListLib.h"
#include "DrawTool.h"

/* Use function OpenFile() from previous assignment */
//PARAMETERS: argc, *argv[] //
FILE *OpenFile(int argc, char *argv[])
{
	//Initializing FileHandle//
	FILE *FH = NULL;
	
	//Initializing the array to store input//
	char input[20];
	
	//If there are less than 2 arguments, prompt for one//
	if(argc < 2)
	{
		printf("\nMust be run with an input file name.\n");
		printf("Enter a file name at the prompt ");
		scanf("%s", input);
	}
	//Otherwise//
	else
	{
		strcpy(input, argv[1]);
	}
	
	//Opening FileHandle//
	FH = fopen(input, "r");
	
	//If FileHandle does not open, keep prompting user until it does//
	while(FH == NULL)
	{
		printf("\nCould not open a file named %s.\n", input);
		printf("\nEnter a file name at the prompt\n");
		
		scanf("%s", input);
		FH = fopen(input, "r");
	}
	
	//RETURN TYPE: //
	return FH;
}

void ReadFileIntoLinkedList(FILE *DCFile, NODE **LinkedListHead)
{
	/* declare various variables needed */
	char buffer[100];
	char *token = NULL;
	char letter;
	char DrawCommand[MAXMAPSIZE];
	
	/* while fgets() reads the file */
	while(fgets(buffer, sizeof(buffer)-1, DCFile))
	{
		/* if line from file ends with \n, then replace \n with \0 */
		if(buffer[sizeof(buffer)-1] == '\n')
		{
			buffer[sizeof(buffer-1)] = '\0';
		}
		
		/* tokenize to get the Letter and the DrawCommand */
		token = strtok(buffer, "|");
		letter = *token;
		
		token = strtok(NULL, "|");
		strcpy(DrawCommand, token);
	
		/* Call AddDrawCommandToList with correct parameters */
		AddDrawCommandToList(letter, DrawCommand, LinkedListHead);
	}
}
