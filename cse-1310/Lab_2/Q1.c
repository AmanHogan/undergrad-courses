// Time taken: 2.5 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main()
{

    //defining variables//
	int N1, N2, M, N;

	//defining "count" as a marker of desired loop iterations//
	int count = 0;

    //asking for user input for N1//
	printf("Enter an integer: ");
	scanf("%d",&N1);

    //Asking for user input for N2//
	printf("Enter an integer: ");
	scanf("%d",&N2);

	//storing inputs into M and N as desired by lab directions//
	 M = N1;
	 N = N2;

    //creating loop that divides every number between  M and N by 11 and records//
    //the number of  0 remainders into count//
	for(int i = M; i <=N; i++)
	{
		if(i%11==0)
		{
			count++;
		}
	}
    //printing the number of 0 remainder divisions by 11 between M and N//
	printf("%d numbers are between %d and %d are multiples of 11",count, M, N);
	printf("\nExiting...");

return 0;

}
