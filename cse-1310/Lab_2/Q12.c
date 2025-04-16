// Time taken: 8 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


//creating function that translates a string to ascii characters//
int userInteger(char message[100]){

    //defining variables//
	char str1[20];

	//getting user input//
	printf("%s", message);
	scanf("%s",&str1);

    //creating conditional that allows user to exit the program//
	if(strcmp(str1, "q")==0){

	printf("Exiting...");

	exit(0);
	}

    //returning ascii value of integers//
	int times = atoi(str1);
	return times;

    }

    //creating loop that repeats certain chracters//
 char repeatLetters(char text[200], int times)
    {
        //deifining variables//
    	int len = strlen(text);

    	//creating loop that goes through entire string//
    	for( int i = 0; i < len; i++ ){

    	printf("%c", text[i]);

            //creating another loop that prints the texts again until N is reached//
    		for( int j = 0; j < times-1; j++){
    		printf("%c",text[i]);
    		}


    	}


    }
    void main()
    {
    	//creating loop that will continue unless user exits//
        while (true)
        {
        	//getting user intput//
            printf("Enter some text, or q to quit: ");
            char text[200];
            gets(text);

            //giving user the option to exit function//
            if (strcmp(text,"q")==0)
            {
                printf("Exiting...\n");
                exit(0);
            }

            //setting value equal to function//
            int times = userInteger("Enter number of times (must be > 0): ");

            //sending text and time to to the function//
            repeatLetters(text, times);

            printf(" \n\n");
        }
    }
