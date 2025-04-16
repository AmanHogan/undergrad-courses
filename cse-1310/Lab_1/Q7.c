    //Time taken: 2.5 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include <stdio.h>
    #include <math.h>

int main(){

    //defining the variables//
    double a;
    int ar, af;

    //asking user to input a double number which will be stored into "a"//
    printf("Please enter a double number: ");
    scanf("%lf",&a);

    //rounding the value of "a" and storing it into "ar"//
    ar = round(a);

    //flooring the value of ""a and storing it into "af"//

    af = floor(a);

    //printing the computed values of "ar" and "af"
    printf("ar = %d, af = %d, ar - af = %d", ar, af, ar-af);

    return 0;

}
