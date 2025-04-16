    //Time taken: 6 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include <stdio.h>
    #include <string.h>

int main(){

    // defining variable//
    char word[20];
    int n;
    int last;

    //asking user to input string and storing into word//
    printf("Please enter a string: ");
    gets(word);
    last=strlen(word);

    //asking user to input integer and storing into n//
    printf("Please enter an integer n: ");
    scanf("%d",&n);

    printf("Output string: ");

    //computing the first half of string using loop that ends when it hits n//

    for(int last=0; last<=n+1; last++){
        printf("$");

        }

    //computing second half of string using loop that ends with '\0'//

    for(int last=n+2; word[last]!= '\0'; last++)
        {

        printf("%c", word[last]);
        }

    return 0;

}




