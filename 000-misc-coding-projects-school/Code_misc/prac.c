#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		char *arg[4];
		arg[0] = (char *)malloc(sizeof(strlen("ls")));
		arg[1] = (char*)malloc(sizeof(strlen("-1")));
		
		
		strncpy(arg[0], "ls", strlen("ls"));
		strncpy(arg[1], "-1", strlen("-1"));
		
		arg[2] = NULL;
		
		
		int ret = execvp(arg[0], &arg[0]);
		if(ret == -1)
		{
			
			perror("execl failed");
			
		}
	}
	else
	{
		int status;
		wait(&status);
			
	}
		






	
}