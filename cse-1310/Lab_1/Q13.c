    //Time taken: 3 minutes //
    // Aman Hogan-Bailey //
    // CSE-1310-007 //
    // Lab 1 //
    // ID: 1001830469 //

    #include<stdio.h>
    #include<math.h>
    #include<string.h>

int main(){

    //defining variables//
    int p =2;
    int n;

    //asking user to input value of their square and storing it in n//
    printf("Please enter the square number: ");
    scanf("%d",&n);

    int geoseq_sum=(1-pow(2,n)/(1-2))-2;

    //using the geometric sequence equation on the n value entered to compute sum value//
    printf("%d gains would be put on the first %d squares", geoseq_sum, n);

    return 0;

}
