// Time taken: 12 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

    //creating function that lowers the case of string sent to it//
char* lowered(char low[100])
	{
	    //defining variables//
		int len = strlen(low);

		//creating loop that lowers each character//
		for(int i = 0; i < len; i++)
			{   //setting character equal to lowered character//
				low[i]= tolower(low[i]);
			}
            //returning lowered character//
			return low;
	}

	//creating function that reverses the order of the original string//
char* reversed(char str1[100]){

    //defining variables//
    int len = strlen(str1);

    //creating loop that starts at one end and starts at the other//
  for(int i = 0, j = len-1; i<j;i++,j--){

    //defining temporary variable//
    char temp = str1[i];
    str1[i] = str1[j];
    str1[j] = temp;}

    return str1;
  }


int main(void) {

	//defining and initializing variables//
  char str1[21]="helLLLLOOO";
  char str2[21]="helLooo";
  char str3[21];

  //printing original string//
  printf("Original %s\n", str1);

  //printing lowered string//
  printf("lowered  %s\n", lowered(str1));

  //copying strings//
  strcpy(str2,lowered(str1));
  strcpy(str3,reversed(str2));

  //printing reversed string//
  printf("reversed %s\n", str3);
}
