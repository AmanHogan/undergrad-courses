#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>


int mails = 0;
pthread_mutex_t mutex;

void *routine(void * arg);

int main()
{


	pthread_t threads[4];
	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < 4; i++)
	{
		pthread_create(&threads[i], NULL, &routine, NULL);

	}

	for(int i = 0; i < 4; i++)
	{
		pthread_join(threads[i], NULL);

	}

	pthread_mutex_destroy(&mutex);

	return 0;
}

void *routine(void *arg)
{
	if(pthread_mutex_trylock(&mutex) == 0)
	{
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}

	else
	{
		printf("Did not get the lock\n");
	}

	

}

