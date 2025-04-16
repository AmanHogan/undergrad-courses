    //Time taken: 6 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>

int main(){

    //defining variables//
    char word[20];
    int length;

    //Asking user to enter a string and storing it in: word//
    printf("Please enter a string: ");
    gets(word);

    // setting length value equal to string length value of word//
    length = strlen(word);

    //printing the pre-output//
    printf("Output string: ");

    if(length>4){for(int length=0; word[length]!='\0'; length++)
        {

        //printing the uppercase letters//
        printf("%c", toupper(word[length]));

        }
                }

    if(length<=4){for(int length=0; word[length] !='\0'; length++)

            //printing lowercase values//
            printf("%c", tolower(word[length]));

                }
    return 0;


}
