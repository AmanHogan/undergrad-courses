#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


#define MAX_THREADS 5


void *routine(void * arg)
{
	int *thread_name = (int *)arg;
	printf("Hello from thread %d\n", *(thread_name));
	
	free(arg);

}



int main()
{
	pthread_t threads[MAX_THREADS];

	int i = 0;
	for(i = 0; i < MAX_THREADS; i++)
	{
		int * thread_id = (int *)malloc(sizeof(int));
		*(thread_id) = 1000 + i; 

		if (pthread_create(&threads[i], NULL, &routine, (void *)thread_id) != 0)
		{
			perror("Could not create thread...");
			exit(0);
		}
	}


	i = 0;
	for(i = 0; i < MAX_THREADS; i++)
	{
		if(pthread_join(threads[i], NULL) != 0)
		{
			perror("Could not join threads...");
			exit(0);
		}
	}

}