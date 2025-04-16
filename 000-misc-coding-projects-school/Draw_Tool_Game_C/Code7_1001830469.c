//Aman Hogan-Bailey MAV-ID: 1001830469//
//Coding Assignment 7//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "ListLib.h"
#include "FileLib.h"
#include "DrawTool.h"

int main(int argc, char *argv[])
{
	//DrawTool Variables//
	char DrawArray[MAXMAPSIZE][MAXMAPSIZE];
	char InputArray[MAXMAPSIZE];
	int MapSize = MAXMAPSIZE;
	
//Initialing variables to be sent to DrawLine()//
	char DrawCommandLines[MAXMAPSIZE];
	char command[MAXMAPSIZE];
	char commandUP;
	char symbol[MAXMAPSIZE];
	char InputArrayUpper[MAXMAPSIZE];
	int xcoordinate;
	int ycoordinate;
	int LineLength;
	int i = 0;
	
	//Initialing LinkedListHead//
	NODE *LinkedListHead;
	LinkedListHead = malloc(sizeof(NODE));
	LinkedListHead = NULL;
	
	//Initializing TempPtr//
	NODE *TempPtr;
	TempPtr = NULL;
	
	//Intializing FileHandle & calling OpenFile()//
	FILE *FileHandle;
	FileHandle = OpenFile(argc, argv);
	
	//Calling ReadFileIntoLinkedList()//
	ReadFileIntoLinkedList(FileHandle, &LinkedListHead);
	
	//Parsing string to get individual inputs//
	char *Token;
	char *Delimeters = "(,)";
	
	//Initializing Map//
	InitializeMap(DrawArray, &MapSize);
	
	//Prompting user for 3 letters//
	printf("Please Enter 1-3 Letters ");
	scanf("%s", InputArray);
	
	int arglength;
	arglength = strlen(InputArray);
	
	//while the entry is fewer than 1 or more than 3, prompt to enter valid input//
	while(arglength < 1 || arglength > 3)
	{
		printf("Invalid Input: Please Enter 1-3 Letters ");
		scanf("%s", InputArray);
		arglength = strlen(InputArray);
	}
	
	//Uppercasing each elemtn of input//
	for(i = 0; i < strlen(InputArray); i++)
	{
		InputArrayUpper[i] = toupper(InputArray[i]);
	}
	
	i = 0;
	TempPtr = LinkedListHead;
	
	//Traversing LinkedList//
	while(i < strlen(InputArray))
	{

		TempPtr = FindLetter(TempPtr, InputArrayUpper[i] , DrawCommandLines);
		
		//Copying Tokens to each individual variable//
		Token = strtok(DrawCommandLines, Delimeters);
		strcpy(command, Token);
		
		commandUP = toupper(command[0]);
		
		Token = strtok(NULL, Delimeters);
		xcoordinate = atoi(Token);
		
		Token = strtok(NULL, Delimeters);
		ycoordinate = atoi(Token);
	
		Token = strtok(NULL, Delimeters);
		LineLength = atoi(Token);
	
		Token = strtok(NULL, Delimeters);
		strcpy(symbol, Token);
		
		DrawLine(DrawArray, xcoordinate, ycoordinate, commandUP, LineLength, symbol[0]);
		i++;
	}
	
	//Calling PrintMap()//
	printf("\n\n");
	PrintMap(DrawArray, MapSize);
	printf("\n\n");
	
	//Upercasing command//
	commandUP = toupper(command[0]);
	
	//closing file//
	fclose(FileHandle);
	
	return 0;
	
	}
