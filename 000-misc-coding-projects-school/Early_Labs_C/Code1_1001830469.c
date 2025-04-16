// Aman Hogan-Bailey ID: 1001830469 //

#include <stdio.h>

int main(void)
{
	int i_i, i_e, j_i, j_e, k_i, k_e;
	
	printf("Enter i's starting value: ");
	scanf("%d", &i_i);
	printf("\n");
	
	printf("Enter i's ending value: ");
	scanf("%d", &i_e);
	printf("\n");

	printf("Enter j's starting value: ");
	scanf("%d", &j_i);
	printf("\n");

	printf("Enter j's ending value: ");
	scanf("%d", &j_e);
	printf("\n");

	printf("Enter k's starting value: ");
	scanf("%d", &k_i);
	printf("\n");

	printf("Enter k's ending value: ");
	scanf("%d", &k_e);
	printf("\n");

	printf("\n\n\n");

	for(int i = i_i; i < i_e; i++)
	{
		for(int j = j_i; j < j_e; j++)
		{
			for(int k = k_i; k < k_e; k++)
			{
				printf("*");
			}	
			printf("\n");
		}
		printf("\n\n");
	}
	return 0;
}