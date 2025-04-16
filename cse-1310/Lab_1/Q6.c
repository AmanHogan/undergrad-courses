    //Time taken: 2 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include<stdio.h>
    #include<math.h>

int main(){

    // variable definition//
    double a;
    int a1, b;

    // User input: entering a double number for a//
    // User input: entering an integer for b//
    printf("Please enter a double number: ");
    scanf("%lf", &a);

    printf("Please enter an integer: ");
    scanf("%ld", &b);

    // casting variable a1 into variable a//
    a1=(int)a;

    //computing results//
    printf("Calculation results: %d %d %d %d", a1+b, a1-b, a1*b, a1/b);

    return 0;


}
