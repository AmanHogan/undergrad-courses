#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int mails = 0;


void *routine(void * arg);
pthread_mutex_t mutex;

int main()
{
	pthread_t p1, p2;
	char * thread1 = "thread 1";
	char * thread2 = "thread 2";

	pthread_create(&p1, NULL, &routine, (void *) thread1);
	pthread_create(&p2, NULL, &routine, (void *) thread2);

	pthread_join(p2, NULL);
	pthread_join(p1, NULL);

	printf("Mail count: %d\n", mails);


	return 0;
}

void *routine(void *arg)
{
	char * thread_name = (char *)arg;
	for(int i = 0; i < 1000000000; i++)
	{
		mails++;
	}

}

