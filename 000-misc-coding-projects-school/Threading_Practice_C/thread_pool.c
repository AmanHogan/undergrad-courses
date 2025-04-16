#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>


typedef struct Task
{
	int a;
	int b;
}Task;


Task taskQueue[256];
int taskCount = 0;
pthread_mutex_t mutexQueue;

void executeTask(Task *task)
{
	int result = task->a + task->b;
	printf("The sum of %d and %d is %d", task->a, task->b, result);
}

void * startThread(coid *args)
{
	while(1)
	{
		pthread_mutex_lock(&mutexQueue);
		if (taskCount > 0)
		{
			Task task;
			task = taskQueue[0];

			for(int i = 0; i < taskCount - 1; i++)
			{
				taskQueue[i] = taskQueue[i+1];
			}
			taskCount--;
		}
		pthread_mutex_unlock(&mutexQueue);



	}

}

int main()
{
	thread_t threads[4];
	pthread_mutext_init(&mutexQueue, NULL);

	for(int i = 0; i < 4; i++)
	{
		int * a = (int *)malloc(sizeof(int));
		*(a) = i;
		pthread_create(&threads[i], NULL, &startThread, (void *)a);
	}

	
	for(int i = 0; i < 4; i++)
	{
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutexQueue);



}