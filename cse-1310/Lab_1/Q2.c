    // Time taken: 2.5 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include<stdio.h>
    #include<math.h>

int main(){

    // variable definition //
    double leg_a, leg_b, area, c2;

    // variable initialization //
    leg_a=3;
    leg_b=4;
    area=(leg_a*leg_b)/2;
    c2=pow(leg_a,2)+pow(leg_b, 2);

    // printing the area and c2 given leg_a=3 and leg_b=4 //
    printf("%.1f\n",area);
    printf("%.1f\n", c2);

    return 0;
}
