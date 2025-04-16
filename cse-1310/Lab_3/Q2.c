// Time taken: 5 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include <stdio.h>
#include <string.h>

//defining macros//
#define max1 4
#define max2 8
#define strlen 10

//creating function that merges arrays//
void arrayMerge(char result[max2][strlen], char a[max1][strlen], char b[max1][strlen])
{

  //creating nested loop that sets first half of r = a//
  for(int i = 0; i < max1; i++)
    {
      for(int j = 0; j < strlen; j++)
        {
            result[i][j] = a[i][j];
        }
    }

    //creating nested loop that sets next half of r = a//
    for(int i = 0; i < max1; i++)
        {
            for(int j = 0; j < strlen; j++)
                {
                   result[i+max1][j] = a[i][j];
                }
        }
  //returning nothing//
  return;

}

//creating function that prints arrays//
 void printStringArray(char name[strlen], char a[max1][strlen], int len)
{
  //printing string that is sent to function//
  printf("%7s: ", name);

  //creating loop that prints array//
  for(int i = 0; i < len; i++)
    {
      printf("%-12s  ", a[i]);
    }
    printf("\n");

  //returning nothing//
  return;
}


int main()
{
  //initializing arrays//
  char a1[max1][ strlen] = {"Arlington", "Plano", "Laredo", "Austin"};
  char b1[max1][ strlen] = {"Amarillo", "McKinney", "Frisco", "Pasadena"};

  //creating array that will store merged arrays//
  char result1[max2][strlen];

  //printing arrays//
  printf("\n");
  printStringArray("a1", a1, max1);
  printStringArray("b1", b1, max1);

  //merging arrays//
  arrayMerge(result1, a1, b1);

  //printing merged arrays//
  printStringArray("result1", result1,max2);

return 0;
  }
