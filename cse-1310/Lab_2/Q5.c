// Time taken: 3 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

int main()
{
    //defining variables//
	int N;

    //asking for user input//
	printf("Enter a positive integer N > 0: ");
	scanf("%d", &N);

    //if user input is less than or equal to 0, the program terminates//
	if(N<=0)
	{
		exit(0);
	}
    //if the input is greater than 0, the program continues//
    //creating nested for loop that prints a * until the N is reached//
	if(N>0)
	{

		for(int i = 0; i<= N-1; i++ )
		{
			for(int j = 0; j<=i; j++)
			{
                //printing * for rows//
				printf("*");
			}
            //printing a next line every row//
			printf("\n");
		}
}

    printf("Exiting...");
return 0;
}



