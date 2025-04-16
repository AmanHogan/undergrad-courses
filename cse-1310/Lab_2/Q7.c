// Time taken: 4 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

    //creates function that counts how many times 'B' or 'b' occurs//
	int countBs(char text[21])
    	{
        //establishing a counter//
    	int count = 0;
    	//creating loop that goes through length of string//
    	for(int i = 0; i< strlen(text); i++)
    		{   //if a a character equals 'b' or 'B' the counter will be added//
    			if(text[i] == 'b'|| text[i]=='B')
    			{
    				count++;
    			}

    		}

        //returning the value of the counter//
        return count;
    	}

   int main() {
       //defining variables//
       char text[21];

        //getting user input//
        printf("Please enter a word: ");
        gets(text);

        //getting the result of the function//
        int result = countBs(text);

        //printing th result of the function//
        printf("%s contains letter B %d times.\n", text, result);

        //returning 0 value//
        return 0;
  }

