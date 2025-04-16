#include <stdio.h>
#include <stdlib.h>

int main()
{
    int A,B;
    int AaB;
    int AoB;
    int nAB;

    printf("Please enter the value of A: ");
    scanf("%d", &A);

    printf("Please enter the Value of B: ");
    scanf("%d", &B);

    if(A ==0 && B==0)
        {
            int AaB =0;
            int AoB = 0;
            int nAB = 1;

    printf("\n\n (A && B) = %d", AaB);
    printf("\n\n (A || B) = %d", AoB);
    printf("\n\n !(A || B) = %d", nAB);
        }
    else if (A == 1 && B == 0)
        {

            int AaB = 0;
            int AoB = 1;
            int nAB = 0;
              printf("\n\n (A && B) = %d", AaB);
    printf("\n\n (A || B) = %d", AoB);
    printf("\n\n !(A || B) = %d", nAB);

        }
    else if(A == 0 && B ==1)
        {
            int AaB = 0;
            int AoB = 1;
            int nAB = 0;
              printf("\n\n (A && B) = %d", AaB);
    printf("\n\n (A || B) = %d", AoB);
    printf("\n\n !(A || B) = %d", nAB);

        }
    else if(A == 1 && B == 1)
        {
            int AaB = 1;
            int AoB = 1;
            int nAB = 0;
              printf("\n\n (A && B) = %d", AaB);
    printf("\n\n (A || B) = %d", AoB);
    printf("\n\n !(A || B) = %d", nAB);


        }


}


