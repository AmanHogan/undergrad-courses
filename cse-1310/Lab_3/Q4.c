// Time taken: 4 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

  #include <stdio.h>

  //defining macros//
  #define rows 5
  #define cols 3

//creating function thats prints arrays//
void printDoubleMatrix(char name[100], double a[rows][cols], int rows1, int cols1)
{
  //printing the name of the array//
  printf("%s:\n", name);

  //creating nested loop that prints arrays//
  for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < cols; j++)
        {
          printf("  %4.1f   ", a[i][j]);

        }
      printf("\n");

    }
    printf("\n");

    //returning nothing//
    return;
}

//creating function that finds the averga eof a given region//
double regionAverage(double A[rows][cols], int topRow, int bottomRow, int leftColumn, int rightColumn)
{
  //creating counters//
  double counter = 0;
  double sum = 0;

  //creating nested loop that adds regions//
  for(int i = topRow; i <= bottomRow; i++)
    {
      for(int j = leftColumn; j <= rightColumn; j++)
        {
          sum = sum + A[i][j];

          counter++;
        }


    }

  //finding avergae value//
  sum = sum/counter;

  //returning sum//
  return sum;

}

int main() {

  //initializing arrays//
  double a[rows][cols] = {  {3.2,2.1,5.3},   {8.0,4.9,5.7},   {18.0,14.9,15.7},   {28.0,24.9,25.7},       {38.0,34.9,35.7}  };

  //calling print function//
  printDoubleMatrix("a", a, rows,cols);

  //calling function that finds region avergae//
  double result = regionAverage(a, 0, 3, 1, 2);

  //calling print function//
  printf("regionAverage(a, 0, 3, 1, 2) returned %.2f.\n", result);

  //setting result equal to value//
  result = regionAverage(a, 2, 4, 0, 2);

  //printing region average//
  printf("regionAverage(a, 2, 4, 0, 2) returned %.2f.\n", result);

return 0;
    }
