// Time taken: 4 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include<stdio.h>
int main()
{
	//intitializing 3d array//
	printf("3D Array Elements\n");
	char arr[3][3][3] =	{
		    {{'A', 'B', 'C'},    {'D', 'E', 'F'},  	{'G', 'H', 'I'}    },
		    {{'J', 'K', 'L'},      {'M', 'N', 'O'},	{'P', 'Q', 'R'}    },
		   {{'S', 'T', 'U'},     {'V', 'W', 'X'},	{'Y', 'Z', '-'}    },
		};

//creating nested loop to print array//
for(int i = 0; i < 3; i++)
{
	for(int j = 0; j < 3; j++)
		{
			for(int k = 0; k < 3; k++)
				{
					printf("%c\t", arr[i][j][k]);

				}
			printf("\n");
		}
	printf("\n\n");
}

return 0;
}
