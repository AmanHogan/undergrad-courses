#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * printName(void *arg)
{
	char * new_name = (char *)arg;
	printf("The name is %s\n", new_name);
	sleep(3);

	return NULL;
}

int main()
{
	pthread_t tid;
	char * name = "Aman Hogan-Bailey";

	pthread_create(&tid, NULL, printName, (void *)name);
	pthread_join(tid, NULL);

	printf("The name has been printed... Exiting program...\n\n");

	return 0;
}