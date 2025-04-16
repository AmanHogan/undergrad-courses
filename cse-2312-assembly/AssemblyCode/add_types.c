#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

extern int32_t add32(int32_t x, int32_t y); 
extern int16_t add16(int16_t x, int16_t y);
extern int8_t add8(int8_t x, int8_t y);

extern uint32_t addU32(uint32_t x, uint32_t y);
//extern uint16_t addU16(uint16_t x, uint16_t y);
//extern uint8_t addU8(uint8_t x, uint8_t y);

int main() {

	uint32_t sum;
	uint32_t a;
	uint32_t b;
	
	a = 63;
	b = 64;
	
	// sum = a + b;
	sum = addU32(a, b);
	
	printf("sum = %d\n", sum);
	
	return EXIT_SUCCESS;
} 
