#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>


sem_t semaphore;

void *routine(void * arg);

int main()
{
	sem_init(&semaphore, 0, 1);

	pthread_t threads[4];

	for(int i = 0; i < 4; i++)
	{
		int * a = (int *)malloc(sizeof(int));
		*(a) = i;
		pthread_create(&threads[i], NULL, &routine, (void *)a);
	}

	
	for(int i = 0; i < 4; i++)
	{
		pthread_join(threads[i], NULL);
	}

	sem_destroy(&semaphore);

	return 0;
}

void *routine(void *arg)
{
	sem_wait(&semaphore);
	sleep(1);
	printf("Hello from thread %d\n", *((int *)arg));
	sem_post(&semaphore);

}

