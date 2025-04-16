// Time taken: 3 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

int main()
    {
    //defining variables//
    int low, high;

    //asking for user input//
    printf("Enter low: ");
    scanf("%d", &low);

    printf("Enter high: ");
    scanf("%d", &high);

    //loop that prints out all numbers between low and high except multiples of 4//
    if(low<=high)
        {
            for(int i = low; i<=high; i++)
                {
                    //condition that if there is a multiple of 4, the loop goes to next iteration//
                    if(i%4==0)
                    {
                    //skipping the body of loop//
                    continue;
                    }
                 printf("%d ", i);
                }
        }
    //setting condition that if low is greater than high then nothing is calculated//
    if(low>high)
        {
        printf("no numbers found");
        exit(0);
        }

return 0;

    }
