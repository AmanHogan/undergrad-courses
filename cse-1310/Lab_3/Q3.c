// Time taken: 4 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include <stdio.h>

//initializing macros//
#define rows 2
#define cols 3

//creating function that prints matricies//
void printDoubleMatrix(char name[cols], double a[rows][cols], int rows1, int cols1)
{
	//printing string sent to function//
    printf("\n%s:\n\t", name);

    //creating nested loop that prints array//
	for(int i = 0; i < rows1; i ++)
		{
			for(int j = 0; j < cols1; j++)
				{
					printf("%.1f\t", a[i][j]);
				}
            printf("\n\t");
		}
	//returning nothing//
	return;
}

//creating function that finds the smallest amounts in array//
void matrixSmallest(double result[rows][cols], double A[rows][cols], double B[rows][cols])
{
	//created nested loop that swaps values//
	for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
				{
					//creating conditional statements to found smallest amount//
					if(A[i][j] < B[i][j])
						{
							result[i][j] = A[i][j];
						}
					else if(A[i][j] > B[i][j])
						{
							result[i][j] = B[i][j];
						}
				}
		}
	//returning nothing//
	return;
}

int main()
{
	//initializing arrays//
	double a1[rows][cols] = {{3.7,2.0,5.6},{9.0,5.9,1.7}};
    double b1[rows][cols] = {{1.1, 2.2,3.3},{4.4,5.5,6.6}};
    double result1[rows][cols];

    //calling printing function//
    printDoubleMatrix("a1", a1, rows, cols);
    printDoubleMatrix("b1", b1, rows, cols);

    //finding smallest values//
    matrixSmallest(result1,a1, b1);

    //calling print function//
    printDoubleMatrix("result1", result1, rows, cols);

return 0;
    }
