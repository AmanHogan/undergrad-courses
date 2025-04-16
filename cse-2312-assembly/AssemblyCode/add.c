#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

extern int32_t add(int32_t x, int32_t y); 

int main() {

	int32_t sum;
	int32_t a;
	int32_t b;
	
	a = -200;
	b = 200;
	
	// sum = a + b;
	sum = add(a, b);
	
	printf("sum = %d\n", sum);
	
	return EXIT_SUCCESS;
} 
