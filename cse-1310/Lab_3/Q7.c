// Time taken: 7 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{   //initializing arrays//
	char line[100];

	//initializing comparison word//
	char word[] = "like";
	//initializing variables//
	char *s;
	int countWord = 0;
	int sum = 0;
	int count;

    //opening files//
	FILE * fp;
	fp = fopen("similes.txt","r");

	//initializing counter variable//
    int i = 1;
    //setting conditional if file is not found//
	if(fp == NULL)
		{
			printf("File not found.");
			exit(0);
		}

    //setting loop to print out array//
    while (true)
    	{
    		if(fgets(line, 100, fp) != NULL)
    			{
                    //printing each line one by one//
                    printf("%d) %s",i, line);

                    //comparing string to line//
            		s = strstr(line, word);

            		//incrementing counter variable//
            		countWord++;

            		//incrementing sum variable//
           			sum = sum + strlen(line);
           			i++;
    			}
            //breaking from loop//
            else break;
    	}
    //closing file//
    fclose(fp);

    //printing total amount of similes and characters//
	printf("\nTotal Similes: %d\nTotal characters in similes.txt: %d", countWord, sum);

return 0;

}
