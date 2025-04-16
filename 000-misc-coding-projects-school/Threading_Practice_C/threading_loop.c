#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int mails = 0;

pthread_mutex_t mutex;

void *routine();

int main()
{
	pthread_t threads[4];
	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < 4; i++)
	{
		if(pthread_create(threads+i, NULL, &routine, NULL) != 0)
		{
			exit(0);
		}

		printf("Thread %d has started\n", i);
	}

	for(int i = 0; i < 4; i++)
	{
		if(pthread_join(threads[i], NULL) != 0)
		{
			exit(0);
		}

		printf("Thread %d has finished\n", i);
	}


	pthread_mutex_destroy(&mutex);
	return 0;
}

void *routine()
{
	for(int i = 0; i < 1000000000; i++)
	{
		mails++;
	}

}

