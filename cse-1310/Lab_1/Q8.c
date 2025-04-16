    //Time taken: 10 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //
    #include <stdio.h>
    #include <string.h>


int main(){

    //defining variables//
    char word[10];
    int n;
    int first,last;

    //asking user to enter a string and storing it to word//
    printf("Please enter a string, at least 5 letters long: ");
    gets(word);

    //asking user to enter an integer and storing it into n//
    printf("Please enter an integer: ");
    scanf("%d",&n);

    //looping to print the first line of text, including "first letter"//
    for(first=0; first < n-2; first++)
        {
        printf("The first letter is %c\n", word[first]);
        }

    //looping to print the second and third lines of text, including "next letter"//
    for(first=1; first <n; first++)
        {

        printf("The next letter is %c\n", word[first]);
        }


    printf("The rest of the string is ");

    //printing the last half of sting subtracting the n value inputed from word length//
    for (last=strlen(word)-n; word[last]!='\0'; last++){
    printf("%c", word[last]);
}

return 0;
}


