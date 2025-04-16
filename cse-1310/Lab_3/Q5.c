// Time taken: 11 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 3 //
// ID: 1001830469 //


#include<stdio.h>

int main()
{
    //intitializing array//
    int arr1D[3] = {10, 20, 30};

    //printing block//
    printf("=====================================================================\n");

    //printiing array details//
    printf("1D Array\n");
    printf("%s = %s\n", "arr1D[3]", "{10, 20, 30};" );
    printf("1D Array\n");

    //creating loop to print array//
    for(int i = 0; i < 3; i++)
        {
            printf("arr1D[%d] = %d\t\t", i, arr1D[i]);
        }
    printf("\n\n");

    //printing block//
    printf("=====================================================================\n");

    //initializing array//
    int arr2D[2][3] = {{10, 20, 30},{40, 50, 60}};

    //initializing array details//
    printf("2D Array\n");
    printf("%s = %s\n","arr2D[2][3]","{{10, 20, 30},{40, 50, 60}};");
    printf("\n\n");

    //printing array using nested loop//
    for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 3; j++)
                {
                    printf("arr2D[%d][%d] = %d\t", i, j, arr2D[i][j]);
                }
            printf("\n");
        }
    printf("\n\n");

    //printing block//
    printf("=====================================================================\n");

    //initializng array//
     int arr3D[4][2][3]  = {{{10, 20, 30},{40, 50, 60}},
                      {{11, 21, 31},{41, 51, 61}},
                      {{12, 22, 32},{42, 52, 62}},
                      {{13, 23, 33},{43, 53, 63}} };

    //printing array details//
    printf("3D Array\n");
    printf("%s = { ","arr3D[4][2][3]");
    printf("%31s\n", "{{10, 20, 30},{40, 50, 60}},");
    printf("%50s\n", "{{11, 21, 31},{41, 51, 61}},");
    printf("%50s\n", "{{12, 22, 32},{42, 52, 62}},");
    printf("%49s\n", "{{13, 23, 33},{43, 53, 63}}");
    printf("3D Array\n");

    //crated nested loop to print array//
    for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 2; j++)
                {
                    for(int k = 0; k < 3; k++)
                        {
                            printf("arr3D[%d][%d][%d] = %d\t", i, j, k, arr3D[i][j][k]);

                        }

                    printf("\n");
                }
            printf("\n");

        }

//printing block//
printf("=====================================================================\n");

return 0;
}
