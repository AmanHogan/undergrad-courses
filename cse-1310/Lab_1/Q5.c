    //Time taken: 2 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include<stdio.h>
    #include<string.h>

int main(){

    //defining the variables//
    char M[10];
    int X;

    //asking user to input a string and integer//
    printf("Please enter a string: ");
    scanf("%s", &M);

    printf("Please enter an integer: ");
    scanf("%d", &X);

    //telling the user their string length//
    printf("The string has length %d.\n", strlen(M));

    //computing the product of the inputed string length and the integer//
    printf("The product is %d.", strlen(M)*X);

    return 0;

}
