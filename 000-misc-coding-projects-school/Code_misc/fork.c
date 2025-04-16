#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	pid_t pid = fork();


	if(pid == -1)
	{
		
		printf("fork failed..");
		exit(0);
	}

	else if(pid == 0)
	{
		printf("Hello from the child!\n");
		sleep(2);
		fflush(NULL);
		return 0;
		
	}	
	
	else
	{
		int status;
		waitpid(pid, &status, 0);
		printf("Hello from the parent process\n");
		fflush(NULL);
	}
	
	return 0;
	
	
	
}