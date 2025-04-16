// Time taken: 10 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool startsWithVowel(char word[21])
    {
    //defining variables//

    //defining variables//
    int len = strlen(word);

    //printing out the details of string//
    printf("len = %d word = %s\n", len, word);

    //creating loop that compares first letter of string to a vowel//
    for(int i = 0; i < 1; i++){

        //statement that ifvowel is a first letter, then true//
    	if(word[i]=='a' || word[i]=='e'||word[i]=='i'||word[i]=='o'||word[i]=='u'||
    	word[i]=='A'||word[i]=='E'||
    	word[i]=='I'||word[i]=='O'||word[i]=='U'){
    	return true;
    	}
    	//statement if value is not a letter then false//
    	else{
    	return false;
    	}

    }


    }





    void main(void)
    {
    	//defining variables//
        char word[21];

        //creating loop that is true until user quits//
         while (true)
        {
           //getting user input//
            printf("Enter some word, or q to quit: ");
            gets(word);

            //statement if q is entered, program quits//
            if (strcmp(word,"q")==0)
            {
                printf("Exiting...\n");
                exit(0);
            }

            //giving value to function//
            bool result = startsWithVowel(word);

            //condition if function is true//
            if (result == true)
            {
                printf("Yes, %s starts with a vowel.\n\n", word);
            }

            //condition if function is false//
            else
            {
                printf("No, %s does not start with a vowel.\n\n", word);
            }
        }
}


