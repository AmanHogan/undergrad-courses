    //Time taken: 4 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>


int main(){

    //variable definition//
    char word[20];
    int l, n;

    //asking user to input string, and storing that string//
    printf("Please enter a string, at least five letters long: ");
    gets(word);

    //variable initialization//
    l=strlen(word);

    //asking user to enter a number less than string length//
    printf("Please enter an integer smaller than the string length: ");
    scanf("%d", &n);


    //printing the precursor final step
    printf("The last 3 letters are: ");

    // printing out the last three letters of entered string by initializing variable:ending//
    for(int ending= l-n; word[ending]!=0; ending++)
        {
        //telling function to repeat a character until word[ending] is proven false//
        printf("%c", word[ending]);
        }
    // printing the required period shown in output//
    printf(".");

    return 0;
}












