#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX 50

char **new_2D_arr();
void free_2D_arr(char **arr);
int get_List(char **arr, struct dirent *entity, DIR *dir);
int dirspace(char folder_picked[40]);

int main()
{
	char folder_picked[40] = ".";
	int sum = dirspace(folder_picked);
	printf("%d", sum);

}


int dirspace(char folder_picked[40])
{
	int total_entries = 0;
	int sum = 0;
	DIR *dir = opendir(".");
	if (dir == NULL)
	{
		printf("An error has occured -- exiting...");
		return 1;
	}
	
	struct dirent *entity = malloc(sizeof(struct dirent) * 100);
	char **list_of_paths = new_2D_arr();
	total_entries = get_List(list_of_paths, entity, dir);
	
	printf("Each entry List: ");
	for(int i = 0; i < total_entries; i++)
	{
		printf("%s\n", list_of_paths[i]);
	}
	printf("\nfor a total of %d entries\n\n", total_entries);
	
	for(int i = 0; i < total_entries; i++)
	{
		strcat(folder_picked, "/");
		strcat(folder_picked, list_of_paths[i]);
		FILE *fp = fopen(list_of_paths[i], "r");
		DIR *dp = opendir(list_of_paths[i]);
		
		if(fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			sum = sum + ftell(fp);
			fclose(fp);
		}
		
		else
		{
			strcat(folder_picked, "/");
			strcat(folder_picked, list_of_paths[i]);
			sum = sum + dirspace(folder_picked);
		}
		
	}	
	
	return sum;
	
	
	
	return 0;
}

int get_List(char **arr, struct dirent *entity, DIR *dir)
{
	int index = 0;
	int total_entries = 0;
	while(entity != NULL)
	{
		strcpy(arr[index], entity->d_name );
		index++;
		total_entries++;
		entity = readdir(dir);
	}
	closedir(dir);
	return total_entries;
}

char **new_2D_arr()
{
	char **arr = malloc(sizeof(char *) * MAX);
	for(int i = 0; i < MAX; i++)
	{
		arr[i] = malloc(sizeof(char) * MAX);
	}
	return arr;
}