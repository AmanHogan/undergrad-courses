// Time taken: 4 minutes //
// Aman Hogan-Bailey //
// CSE-1310-007 //
// Lab 2 //
// ID: 1001830469 //

#include <stdio.h>
#include <string.h>

//defining function that converts string into atoi number//
int user_integer(char message [100]){

	//defining variables//
	char str1[100];
	int num;

    //asking for user input//
	printf("%s", message);
	scanf("%s", str1);

    //converting string into number//
	num = atoi(str1);

    //returning number//
	return num;
   }


//creating function that chooses the middle number//
int pickMiddle(int a, int b, int c){
    //if a is middle//
	if(a>b && a<c){
	return a;
	}
    //if b is middle//
	else if(b>a && b<c){
	return b;
	}
    //if c is middle//
	else if(c>b && c<a){
	return c;
	}

}



int main(void) {

    //asking for user input//
    int N1 = user_integer("Enter number N1: ");
    int N2 = user_integer("Enter number N2: ");
    int N3 = user_integer("Enter number N3: ");

    //printing the middle number//
    printf("middle %d\n", pickMiddle(N1,N2,N3));


return 0;
}
