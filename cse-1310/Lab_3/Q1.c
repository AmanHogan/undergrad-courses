// Time taken: 3 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <strings.h>

//defining macros//
#define N 5

//printing the array that is sent to the function//
void printDoubleArray(char name[10], double a[N], double n)
    {
        //printing string that is sent to function//
        printf("%15s: ", name);

        //creating loop that will print array//
        for(int i = 0; i < n; i++)
            {
                printf("%5.2f   ", a[i]);
            }
        printf("\n");

        //returning nothing//
        return;
    }

//creating new array information in sent array//
double *arraySquare(double A[N])
    {
        //creating a global array//
        static double R[N] = {0};

        //creating loop that will store new values in R//
        for(int i = 0; i < N; i++)
            {
                R[i] = pow(A[i], 2);
            }

        //returning R//
        return R;
    }

int main()
{
    //initializing the arrays//
    double a[] = {3.2, 2.1, 5.3, 8.0, 4.9};
    double b[] = {1.1, 2.2, 3.3, 4.4, 5.50};

    //storing address of array into result//
    double *result = arraySquare(a);

    //printing arrays//
    printDoubleArray("a1", a, N);
    printDoubleArray("arraySquare(a1)", result, N);

    //storing value in result//
    result = arraySquare(b);

    //printing arrays//
    printf("\n");
    printDoubleArray("b1", b,N);
    printDoubleArray("arraySquare(b1)", result, N);

return 0;
}
