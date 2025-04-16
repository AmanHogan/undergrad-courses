/*

	Name: Aman Hogan-Bailey
	ID: 1001830469

*/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"
#define MAX_COMMAND_SIZE 255 
#define MAX_NUM_ARGUMENTS 11
#define MAX_HIST_SIZE 15

int main()
{
	//flag variable that will show whether the user string
	//was a previously used string or not
	int flag = 0;
	
	//variables shows the number of processes created and
	//the number of times a commands have been entered
	int pid_index = 0;
	int pid_hist_index = 0;
	int i = 0;
	
	//will hold the commands entered by the user
	char *command_string = (char*)malloc(MAX_COMMAND_SIZE);
	
	//will hold the history of commands entere by the user
	char history[MAX_HIST_SIZE][MAX_COMMAND_SIZE];
	
	//will hold the pids of prcesses created
	pid_t pid_history[MAX_HIST_SIZE];
	
	
	//clearing out the array that will hold the history of commands used
	//this ensures that no garbage will be stored in the array
	for(i = 0; i < MAX_HIST_SIZE; i++)
	{
		memset(history[i], 0 , MAX_HIST_SIZE);
	}
	
	i = 0;
	//making sure the array that will hold the pids will not have
	//garbage inside by setting them to '0'
	for(i = 0; i < MAX_HIST_SIZE; i++)
	{
		pid_history[i] = 0;	
	}
	
	//getting the pid of the initial process and storing it in the array that
	//holds a history of pids in the program.
	//incrementing the counter variable to get the next pid
	pid_history[pid_hist_index] = getpid();
	pid_hist_index++;
	
	//unless specified otherwise, the program will continue
	while(1)
   {
		//if the number of processes ran is greater than 14,
		//restart the index number at 0
		if(pid_index > 14)
		{
			pid_index = 0;
			pid_hist_index = 0;
		}
	
		fflush(stdin);
		
		//if the user did not enter "!n" in the command line, then get the commands normally through
		//the standard input.
		//flag variable will only be set to q if "!n" is entered.
		if(flag != 1)
		{
			//get the command line from the user and store it
			printf ("msh> ");
			while(!fgets(command_string, MAX_COMMAND_SIZE, stdin));
			
			//set flag back to 0, to avoid infinte loop
			flag = 0;
		}
		
		//set flag back to 0, to avoid infinite loop
		flag = 0;

		//holds number of parsed tokens from the command line
		int token_count = 0;
		
		//array will hold the parsed tokens from the command line
		char *token[MAX_NUM_ARGUMENTS];                              
		
		//temporary string pointer used to hold intermediate string
		char *argument_ptr;

		//string will hold the contents from the command line
		//strsep will move the pointeer ahead so we must save it
		char *working_string  = strdup( command_string );                
		char *head_ptr = working_string;
		
		//tokenize the command line until the end is a NULL
		while (((argument_ptr = strsep(&working_string, WHITESPACE)) != NULL) && (token_count<MAX_NUM_ARGUMENTS))
		{
			token[token_count] = strndup(argument_ptr, MAX_COMMAND_SIZE);
			
			//if the string length of the command is 0, set the string
			//equal to 0
			if(strlen(token[token_count]) == 0)
			{
				token[token_count] = NULL;
			}
			token_count++;
		}

		int token_index  = 0;
		
		//if the user had not entered anything in the command line,
		//peacefully continue and prompt user again for input
		if(token[0] == NULL)
		{
			continue;
		}
		
		//if user entered "quit" or "exit", leave the program
		if(strcmp(token[0], "quit") == 0 || strcmp(token[0], "exit") == 0)
		{
			return 0;
		}

		//if "history" is entered into the command line, loop through the 
		//array that holds a history of commands,so far, and print their contents
		//to the console
		if(strcmp(token[0], "history") == 0)
		{
			i = 0;
			for(i = 0; i < pid_index; i++)
			{
				printf("%d: %s\n", i, history[i]);
			}
		}
		
		//if "pidhistory" is entered into the command line, loop throguh the 
		//array that holds the pids of the created processes, so far, and 
		//print their contents to the console
		if(strcmp(token[0], "pidhistory") == 0)
		{
			i = 0;
			for(i = 0; i < pid_index; i++)
			{
				printf("%d: %d\n", i, pid_history[i]);
			}
		}
		
		//frees the memmory allocated for the command string, that was
		//vicariously alloacted to the head_ptr string
		free(head_ptr);
		
		//if "cd" was entered into the command line, change the directory
		if(strcmp(token[0], "cd") == 0)
		{
			if(chdir(token[1])!=0)
			{
				perror("chdir() failed: ");
			} 
		}
		
		// variable holds the number/index of the command to be re-run 
		int index = 0;
		
		// if the command entered begins with a '!', then chack to see if the 
		// user follwed the format: "!n"
		if(token[0][0] == '!')
		{
			// creating a string that will hold the string version of the
			// number that the user enters, "n"
			// this will allow us to convert a string to an integer seamlessly 
			char val[2] = "";
			
			//setting index to 0
			index = 0;
			
			//string equals the 1st and 2nd characters entered in the command line
			val[0] = token[0][1];
			val[1] = token[0][2];
		
			//convert string to integer
			index = atoi(val);
			
			//if the entered number, "n", is greater than the number of times the commandline has been prompted,
			//then it does not exist in the pidhistory
			//reprompt the user the bash shell
			if(index > pid_index)
			{
				printf("Command not in history\n");
				continue;
			}
			
			//if the index is valid then...
			if(index <= 14 && index >= 0 )
			{
				//zero out the current command line so garbage is not in there
				memset(command_string,0,strlen(command_string));
				
				//copy the command that the user wanted in the history into the command string
				strcpy(command_string, history[index]);
				
				//flag indicates that the user wants a command that has already been entered, 
				//and to skip asking for input
				flag = 1;
				
				//re-call the while loop without prompting for input
				continue;
			}
		}
		
		//create a child process
		//pid will recieve the child pid if it is the parent
		//pid will be 0 if it is the child pid
		pid_t pid = fork();
		
		//if this is the child execute the command from the command line
		if(pid == 0)
		{
			//if command is not: "pidhistory", "cd", "histoy", then find the program specified
			//the following if commands were split into two if's, to avoid 
			//exceding the 100 charcters per line requirement
			if( !(strcmp(token[0],"cd")==0) )
			{
				//if command is not: "pidhistory", "cd", "histoy", then find the program specified
				if( !(strcmp(token[0],"history")==0) && !(strcmp(token[0],"pidhistory")==0))
				{
					//find program with the name in token[], and execute it
					int ret = execvp(token[0], token);
					
					//if ret returns -1, show user that the command couldnt be found and destroy this process
					printf("%s: Command not found.\n", token[0]);
					exit(0);
				}
			}
	
			//destroy this process whether an error occurs or not
			exit(0);
		}

		//let the parent process wait for the child
		else 
		{
			int status;
			wait(&status);
			
			//when the child finishes, record the pid number of the child into an array
			pid_history[pid_hist_index] = pid;
		}
		
		i = 0;
		//creatign a string that will hold all the tokenized command line componets
		char buff[255] = "";
		
		//for tokenized string from the command line, copy it into the new string
		//this will create a string identical to the string originally input
		//into the command line
		for(i = 0; i < token_count; i++)
		{
			if(token[i] != NULL)
			{
				strcat(buff, token[i]);
				
				//then concatenate it with a space
				strcat(buff, " ");
			}
		}
		
		//copy the newly create string into the history of commands
		strcpy(history[pid_index], buff);
		
		//increment the counter represdenting the number of processes that have been ran so far
		pid_index++;
		pid_hist_index++;
		flag = 0;
   }
	return 0;
}
