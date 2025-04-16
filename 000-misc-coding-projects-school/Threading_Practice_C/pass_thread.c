#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


char primes[10] = {2,3,5,7,11,13,17,19,23,29};


void *routine();

int main()
{
	pthread_t threads[10];

	for(int i = 0; i < 10; i++)
	{
		int *ind = (int *)malloc(sizeof(int));
		*(ind) = i;

		if (pthread_create(threads + i,NULL, &routine, (void *)ind) != 0)
		{
			perror("Failed to create thread");
		}
	}



	for(int i = 0; i < 10; i++)
	{

		if (pthread_join(threads[i], NULL) != 0)
		{
			perror("Failed to join thread");
		}
	}


	return 0;
}

void *routine(void * arg)
{
	int *j = (int *)arg;
	printf("%d, ", primes[*(j)]);
	free(arg);

}
