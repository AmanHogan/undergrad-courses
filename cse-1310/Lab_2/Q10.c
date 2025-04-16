// Time taken: 5 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//creating function that allows user to quit and displays radius//
double user_msg(message){

    //defining variables//
	char str1[100];
    double R;

    //getting user input//
	printf("%s", message);
	scanf("%s", &str1);

	//creating id statement that allows user to quit//
	if(strcmp(str1, "q")==0){
	printf("Exiting...");
	exit(0);
	}

        //converting string into double//
        R = (double) atof(str1);


    //returning value//
    return R;
    }


//creating function that calculates volume//
double volume(double R){

    //calculating volume//
    double volume_s = M_PI* pow(R,3)* (double)4/3;

    //returning volume//
    return volume_s;
}

int main(void) {

    //defining variables//
    double R=0;

    while (true){

    	//setting R equal to user message//
        R = user_msg("\nEnter radius: ");

        //printing the radius//
        printf("Radius = %0.2f\n",R);

        //printing the volume//
        printf("volume of sphere with radius (%0.2f) is %0.2f\n",R, volume(R));
    }
return 0;
}
