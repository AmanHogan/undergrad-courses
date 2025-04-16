#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>



int main()
{
	int pid = fork();
	int n;

	if(pid == 0)
	{
		n = 1;
	}

	else
	{
		n = 6;
	}


	for(int i = 0; i < n + 5; i++)
	{
		printf("%d ", i);
	}

}