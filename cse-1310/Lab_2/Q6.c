// Time taken: 14 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

    //creating function that return the occurrences of str1//
 int countOccurrences(char str1[21], char c_occur ) {

    //defining variables//
    int count = 0;
    int len = strlen(str1);

        //creating loop that compares the string letter to the character sent to this function//
        for(int i = 0; i <len; i++){
            if(str1[i]==c_occur){

             count++;


    }


    }
    return count;
    }
    //creating function that finds the most frequently occurring character//
char mostFrequentCharacter(char text[21]) {

    //defining variables//
    int max_value = 0;
    int length = strlen(text);
    char max_char = '1';


    //creating loop that logs the max character and returns it to main function//
    for(int i = 0; i<length-1; i++){

        int occur = countOccurrences(text, text[i]);

        //if the occurrance is greater than the max, max becomes occurrance//
        if(occur > max_value){

            //setting variables equal to each other//
            max_value = occur;
            max_char = text[i];


        }
    }

return max_char;

    }


   int main() {
       //defining variables//
       char text[21];

        //creating loop that allows user to quit//
        while (true) {
            printf("Enter some text, or q to quit: ");
            gets(text);
            if (strcmp(text,"q")==0) {
                break;
            }
            if (strlen(text) == 0) {
                break;
            }
            //setting values to functions//
            char c = mostFrequentCharacter(text);
            int number = countOccurrences(text, c);

            //printing out results//
            printf("Most frequent character: '%c'\n", c);
            printf("Number of occurrences of '%c': %d\n\n", c, number);
        }
        printf("Exiting...\n");
    return 0;
  }

