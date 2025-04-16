//Aman Hogan-Bailey MAV-ID: 1001830469//

#include <stdio.h>
#include <stdlib.h>
#include "DrawTool.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main()
{
	//initializing variables//
	char DrawArray[MAXMAPSIZE][MAXMAPSIZE];
	char InputArray[MAXMAPSIZE];
	int MapSize = 0;
	
	//Initialing variables to be sent to Draw Command//
	char command[MAXMAPSIZE];
	char commandUP;
	char symbol[MAXMAPSIZE];
	char symbolNEW;
	int x;
	int y;
	int length;
	
	//Parsing string to get individual inputs//
	char *Token;
	char *Delimeters = "(,)";
	
	//Initializing Map and printing instructions to the screen//
	InitializeMap(DrawArray, &MapSize);
	PrintInstructions();
	
	//Formatting and printing map//
	printf("\n\n");
	PrintMap(DrawArray, MapSize);
	printf("\n\n");
	
	//prompting for input//
	printf("Enter draw command (enter Q to quit) ");
	fgets(InputArray, MAXMAPSIZE-1, stdin);
	printf("\n\n");
	
	//copying to command//
	Token = strtok(InputArray, Delimeters);
	strcpy(command, Token);
	
	//Upercasing Command//
	commandUP = toupper(command[0]);
	
	//Creating while loop that stops when Q or q is entered//
	while(commandUP != 'Q')
	{
	
		//Copying Tokens to each individual variable//
		Token = strtok(NULL, Delimeters);
		x = atoi(Token);
	
		Token = strtok(NULL, Delimeters);
		y = atoi(Token);
	
		Token = strtok(NULL, Delimeters);
		length = atoi(Token);
	
		Token = strtok(NULL, Delimeters);
		strcpy(symbol, Token);
		
		//If the first element of symbol is ENTER or a NULL terminator, set it equal to X//
		if(symbol[0] == '\n')
		{
			symbolNEW = 'X';
		}
		
		else
		{
			symbolNEW = symbol[0];
		}
		
		//If the command does not equal any of the accpeted draw command, print this://
		if(commandUP != 'P' && commandUP != 'V' && commandUP != 'H')
		{
			printf("That draw command is unknown.");
		}
		
		if(commandUP == 'P')
		{
			length = 1;
		}
		
		//If Draw command is out of Bounds, print this message//
		if(commandUP == 'V' && (x + length) > MapSize )
		{
			printf("That draw command is out of range.");
		}
		
		else if(commandUP == 'H' && (y + length) > MapSize)
		{
			printf("That draw command is out of range.");
		}
		
		else if((x < 0) || x >= MapSize || (y < 0) || (y >= MapSize))
		{
			printf("That draw command is out of range.");
		}
	
		else if(commandUP != 'P' && commandUP != 'V' && commandUP != 'H')
		{
			//Dont write and continue to prompt//
		}
		//If Draw command is within bounds, call DrawLine()//
		else
		{
			DrawLine(DrawArray, x, y, commandUP, length, symbolNEW);
		}
		
		//Formatting and printing map//
		printf("\n\n");
		PrintMap(DrawArray, MapSize);
		printf("\n\n");
		
		//prompting for input//
		printf("Enter draw command (enter Q to quit) ");
		fgets(InputArray, MAXMAPSIZE-1, stdin);
		printf("\n\n");
		
		//copying to command//
		Token = strtok(InputArray, Delimeters);
		strcpy(command, Token);
	
		//Upercasing command//
		commandUP = toupper(command[0]);
		
	}
	
	return 0;
}
