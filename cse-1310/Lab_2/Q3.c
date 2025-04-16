// Time taken: 2 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    //defining variable N//
	int N;

    //asking user to input value that is positive into N//
	printf("Enter a positive integer N > 1: ");
	scanf("%d", &N);

    //condition that if N is less than 1, then program will not operate//
	if(N<=1)
	{
		exit(0);
	}
    //condition that if N is greater than 1, then program will operate//
	if(N>1)
	{
        //creating loop that will repeat until the power of N is less than or equal to 40000//
		for(int i = 0; pow(N,i) < 40000; i++)
		{
			//setting result equal to power of N//
			int result = pow(N, i);

			//printing result until condition is proven false//
			printf("%d ", result);

		}


	}

    printf(" Exiting...");
return 0;
}
