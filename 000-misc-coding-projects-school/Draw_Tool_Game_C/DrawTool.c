//Aman Hogan-Bailey MAV-ID: 1001830469//
//Coding Assignment 7//

#include <stdio.h>
#include "DrawTool.h"

void InitializeMap(char Map[][MAXMAPSIZE], int *MyMapSize)
{
	int j, k;
	char Background = ' ';
	
	while (*MyMapSize < 1 || *MyMapSize > MAXMAPSIZE)
	{
		printf("That value is outside of the max bounds of the array.  Please reenter\n\n");
		printf("How big is the array? (Enter a value between 1 and %d) ", MAXMAPSIZE);
		scanf("%d", MyMapSize);
	}
	
	printf("What is the background character? ");
	scanf(" %c", &Background);
	
	/* Initialize Map to the entered background character */
	for (j = 0; j < *MyMapSize; j++)
	{
		for (k = 0; k < *MyMapSize; k++)
		{
			Map[j][k] = Background;
		}
	}
}

void DrawLine(char Map[][MAXMAPSIZE], int from, int to, char LineType, int count, char mark)
{
	int j;
	
	if (LineType == 'H')     
	{
		for (j = 0; j < count; j++)
		{
			Map[from][to+j] = mark;
		}	
	}
	else
	{	
		for (j = 0; j < count; j++)
		{
			Map[from+j][to] = mark;
		}		
	}
}

void PrintMap(char Map[][MAXMAPSIZE], int MyMapSize)
{
	int i, j;
	
	printf("\n\n");
	
	for (i = 0; i < MyMapSize; i++)
	{
		for (j = 0; j < MyMapSize; j++)
		{
			printf("%c  ", Map[i][j]);
		}
		printf("\n");
	}
}	


