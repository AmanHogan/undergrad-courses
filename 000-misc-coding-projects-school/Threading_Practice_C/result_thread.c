#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



void *roll();

int main()
{
	pthread_t thread;
	int *res;
	srand(time(NULL));

	if(pthread_create(&thread, NULL, &roll, NULL) != 0)
	{
		printf("A thread could not be created...\n");
		exit(0);
	}

	if(pthread_join(thread, (void **)&res) != 0)
	{
		printf("A thread could not be joined...\n");
		exit(0);
	}

	printf("\n%d", *res);





	return 0;
}




void *roll()
{
	int value = (rand() % 6)+1;
	int *result = malloc(sizeof(int));
	*result = value;

	printf("%d\n", value);
	
	return result;
}

