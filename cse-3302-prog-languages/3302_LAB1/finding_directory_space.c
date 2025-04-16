// Aman Hogan-Bailey
// 1001830469
// gcc Version 9.3.0
// Ubuntu (20.04.1 LTS (Focal Fossa)) [CSE 1320 Virtual Machine]


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define MAX 50

char **new_2D_arr();
void free_2D_arr(char **arr);
int getEntries(char **entries, struct dirent *entity, int entry_types[MAX], char path[MAX]);
int dirspace(char path[MAX]);

//Function prints total size of files in directory & subdirectories
int main()
{
	//Initializing the files' total & current path
	int sum = 0;
	char intit_path[MAX] = ".";
	
	//Calling function that returns filess' total & printing it
	sum = dirspace(intit_path);
	printf("%d", sum);
}

//Function returns total size of files in directories & subdirectories recursively
int dirspace(char path[MAX])
{
	//Holds number of entries in current directory
	int count = 0;
	
	//Initializing initial file size in current directory
	int sum = 0;
	
	//Initializing a struct pointer that holds info about entries
	struct dirent *entity = malloc(sizeof(struct dirent) * 100);
	entity = NULL;
	
	//Creating a 2D array that will hold a list of  "*enitity"
	//returns newly allocated 2D array
	char **entries = new_2D_arr();
	
	//Creating an array that holds the type of entity (Directory or File)
	int entry_types[MAX] = {0};
	
	//Calling function that fills the list of entries and types
	//returns number of entries found
	count = getEntries(entries, entity, entry_types, path);
	
	
	for(int i = 0; i < count; i++)
	{
		//If the entry in the list is a directory call "dirspace" - recursion
		if(entry_types[i] == 4)
		{
			//Intializing and concatenating the path with the name of entry
			char new_path[MAX] = {0};
			strcat(new_path, path);
			strcat(new_path, "/");
			strcat(new_path, entries[i]);
			
			//Calling the function recursively
			sum = sum + dirspace(new_path);
		}
		
		//If the entry in the list is a file get size of the file
		else if(entry_types[i] == 8)
		{
			//Intializing and concatenating the path with the name of entry
			char new_path[MAX] = {0};
			strcat(new_path, path);
			strcat(new_path, "/");
			strcat(new_path, entries[i]);
			
			//Opening file using the path
			FILE *fp = fopen(new_path, "r");
			
			//Using fseek() method to get file size
			fseek(fp, 0, SEEK_END);
			sum = sum + ftell(fp);
			fclose(fp);
		}
	}	
	return sum;
}

//Function fills a 2D array with a list of entries in the current directory
//returns the total number of entries found
int getEntries(char **entries, struct dirent *entity, int entry_types[MAX], char path[MAX])
{
	//Opening directory
	//If directory is not found, return -1
	DIR *dir = opendir(path);
	if (dir == NULL)
	{
		printf("An error has occured -- exiting...");
		return 1;
	}
	
	//Initialing index of 2D array and total entries
	int index = 0;
	int total = 0;
	
	//Read the directory return a point to "entity"
	entity = readdir(dir);
	
	//While there is still an entry in the directory, that has not been read...
	//make "entity" equal to that entry found
	while(entity != NULL)
	{
		//If the entry found is a directory to previous or current directory, skip it
		if((strcmp("", entity->d_name) == 0)||(strcmp(".", entity->d_name) == 0)||(strcmp("..", entity->d_name) == 0))
		{
			entity = readdir(dir);
			continue;
		}
		
		//Copy the entry name and type to the 2D array
		strcpy(entries[index], entity->d_name );
		entry_types[index] = entity->d_type;
		
		//Increment total and index
		index++;
		total++;
		
		//Get new entry and set it equal to "entity"
		entity = readdir(dir);
	}
	closedir(dir);
	return total;
}

//Function allocates space for a new 2D array
//Returns 2D array
char **new_2D_arr()
{
	//Allocate size for array
	char **arr = malloc(sizeof(char *) * MAX);
	
	//Allocate space for columns
	for(int i = 0; i < MAX; i++)
	{
		arr[i] = malloc(sizeof(char) * MAX);
	}
	
	//Allocate space for rows
	for(int i = 0; i < MAX; i++)
	{
		for(int j = 0; j < MAX; j++)
		{
			arr[i][j] = '\0';
		}
	}
	return arr;
}