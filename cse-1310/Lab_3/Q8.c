// Time taken: 7 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //

#include<stdio.h>
#include<math.h>

//defining macros//
#define N 5
#define K 20

//prototyping functions//
void printArray(char name[K], double a[N], int n);
void fprintArray(FILE *f, char name[K], double a[N], int n);
double * arrayArea(double A[N]);
double * arrayCirc(double A[N]) ;

//initialzing globbal varaibles//
static double Circ[N] = {0};
static double Area[N] = {0};


int main() {

    //initializing names//
    char outArea[K] = "outArea.txt";
    char outCirc[K] = "outCirc.txt";

    //initializing the writing of files//
    FILE * fwArea=fopen(outArea,"w");
    FILE * fwCirc=fopen(outCirc,"w");

    //initializing an array of radii
    double radius1[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    //calling an array of circumferences
    *arrayCirc(radius1);

    //calling an array of areas
    *arrayArea(radius1);

    //print the array of radius on screen
    printArray("radius1", radius1, N);

    //print the array of radius in a file (outArea.txt)
    fprintArray(fwArea, "radius1", radius1, N);

    //print the array of area on the screen
    printArray("Area(radius1)", Area, N);

    printf("\n\n");

    //print the array of area in a file (outArea.txt)
    fprintArray(fwArea, "Area(radius1)", radius1, N);

    //print the array of radius on screen
    printArray("radius1", radius1, N);

    //print the array of radius in a file (outCirc.txt)
    fprintArray(fwCirc, "radius1", radius1, N);

    //print the array of circumference on the screen
    printArray("Circumference(radius1)", Circ, N);


    //print the array of circumference in a file (outCirc.txt)
    fprintArray(fwCirc, "Circumference(radius1)", Circ, N);


    // close files
    fclose(fwArea);
    fclose(fwCirc);

    }


//prints the contents of an integer array in a file identified by the file identifier f
void fprintArray(FILE *f, char name[K], double a[N], int n)
{
    fprintf(f, "%22s: ", name);
    for(int i = 0; i < n; i++)
    {
        fprintf(f, "%5.2f   ", a[i]);
    }
    fprintf(f, "\n");
    return;
}



//prints the contents of an integer array
void printArray(char name[K], double a[N], int n)
{
    printf("%22s: ", name);

    //creating loop that prints array//
    for(int i = 0; i < n; i++)
        {
            printf("   %5.2f", a[i]);
        }
    printf("\n");

return;
}

//accepts an integer array (of radius) as an input parameter
//returns an array of Circumference
double *arrayCirc(double A[N])
{
    for(int i = 0; i < N; i++)
        {
            //creating loop that creates circumference//
            Circ[i] = 2 * M_PI * A[i];
        }
    return Circ;
}


//accepts an integer array (of radius) as an input parameter
//returns an array of Area
double *arrayArea(double A[N])
{
    for(int i = 0; i < N; i++)
        {
            //creating loop the creates area//
            Area[i] = M_PI * pow(A[i], 2);

        }
    return Area;
}
