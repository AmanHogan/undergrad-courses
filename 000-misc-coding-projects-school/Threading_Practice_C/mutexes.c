#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int mails = 0;
pthread_mutex_t mutex;

void *routine(void * arg);

int main()
{
	pthread_t p1, p2;
	pthread_mutex_init(&mutex, NULL);

	char * thread1 = "thread 1";
	char * thread2 = "thread 2";

	pthread_create(&p1, NULL, &routine, (void *) thread1);
	pthread_create(&p2, NULL, &routine, (void *) thread2);

	pthread_join(p2, NULL);
	pthread_join(p1, NULL);

	printf("Mail count: %d\n", mails);


	pthread_mutex_destroy(&mutex);
	return 0;
}

void *routine(void *arg)
{
	char * thread_name = (char *)arg;
	for(int i = 0; i < 100000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}

}

