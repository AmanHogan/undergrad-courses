
//Aman Hogan-Bailey//
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    uint8_t a = 0;
    uint8_t b = 6;
    
     printf("a\ta == b\ta < b\ta > b");
    
    for(int i = 0; i < 512; i++, a++)
    {
       
        printf("\n\n");
        
        printf("%d\t%d\t%d\t%d", (a), (a==b), (a<b), (a>b));
        
        printf("\n\n");
        
        
    }
    
    return 0;
    
}
