    // Time taken: 4 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include<stdio.h>
    #include<math.h>

int main(){

    // variable definition//
    double c, m, v, m_rel, E;

    //variable initialization//
    c=300000000;

    //User input: mass//
    printf("Please enter the mass of the spacecraft (kg): ");
    scanf("%lf", &m);

    //User input:moving velocity
    printf("Please enter the moving speed of the spacecraft (m/s): ");
    scanf("%lf", &v);

    // computation//
    m_rel=m/sqrt(1-pow(v,2)/pow(c,2));
    E=m_rel*pow(c,2);

    //printing results//
    printf("%.1f kg\n",m_rel);
    printf("%.1f J\n", E);

    return 0;


}

