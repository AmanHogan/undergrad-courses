// Time taken: 2 minutes //
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

	//designing count to use as a marker//
	int count;

	//asking for user input//
	printf("Enter an integer N: ");
	scanf("%d", &N);

	//using for loop that marks everytime N=i*i+i//
	for(int i = 1; i<=N; i++)
	{
		if(N==i*i+i)
		{
			count++;
		}
	}

	//if the count was more than once, then the statement will be printed//
	if(count>0)
	{
		printf("%d is a holy number in Numerion.", N);

	}
	//if the count never happended in the loop, then this statement will be printed//
	else if(count <=0)
	{
		printf("%d is not a holy number in Numerion.", N);
	}

        printf("\nExiting...");

return 0;

}
