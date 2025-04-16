// Time taken: 16 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#define SIZE 200

//initializing global variables//
static char line2[SIZE] = {0};
static char line3[SIZE] = {0};

//prototyping functions//
char *firstWord(char line[SIZE], int N);
char *lastWord(char line[SIZE], int N);

int main()
{
    //initializing variables//
  int counter = 1;
  char bigline[200];

  //initializing file variables//
  FILE * fr = fopen("idioms.txt","r");
  FILE * fw = fopen("outFirst.txt", "w");
  FILE * fw1 = fopen("outlast.txt", "w");

    //setting conditional if file is not found//
  if(fr == NULL)
    {
      printf("File does not exist.");
      exit(0);
    }

    //creating loop to go through files and print to console//
  while (true)
    {
        //printing a line to the console from file//
      if(fgets(bigline, 200, fr) != 0)
        {
            //printing the string to the console//
          printf("%d) %s",counter, bigline);
          int n = strlen(bigline);

          //setting s equal to called function//
          char *s = firstWord(bigline, n);

          //printing first word//
          printf("first:%s", s);

            //setting s2 equal to called function//
          char *s2 = lastWord(bigline, n);

          //printing last word//
          printf("\tlast:%s", s2);
        printf("\n");

        //printing strings and first word to file//
        fprintf(fw, "%d) %sfirst:%s\n\n",counter, bigline, s);

        //printing last word and string to the file//
        fprintf(fw1, "%d) %slast:%s\n",counter, bigline, s2);

        //incrementing counter//
        counter++;
        }
    //breaking from loop when end of file is reached//
      else
        {
          break;
        }
    }
    //closing file//
  fclose(fr);
  fclose(fw);
  fclose(fw1);

return 0;
}

//creating function that prints first word//
char *firstWord(char line[SIZE], int N)
    {
        //creating loop that prints first word//
        for(int i = 0; line[i] != '\0'; i++)
            {
                    //leaving loop if a space is reached//
                if(line[i] == ' ')
                    {
                        break;
                    }
                //setting new line equal to old line//
                line2[i] = line[i];
            }

        //returning new line//
        return line2;
    }

//creating function that prints last word of string//
char *lastWord(char line[SIZE], int N)
    {
        //initializing variables and length//
        int i=0;
        int length = strlen(line);

        for(i = length-2; i >= 0; i--)

            {
                //breaking from loop if space is reached//
                if(line[i] == ' ')
                    {
                        break;
                    }

            }
        //returning the address of line//
       return &line[i];
    }
