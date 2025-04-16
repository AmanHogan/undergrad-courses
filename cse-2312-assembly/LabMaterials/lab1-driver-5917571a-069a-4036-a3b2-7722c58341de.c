/* CSE 2312 - Fall 2021 - Lab 1 Driver
 *
 * Programming Lab Policies:
 *  - Labs that fail to compile, or do not terminate correctly, will receive a zero.
 *  - Labs that fail to compile, or do not terminate correctly, may not be resubmitted for a grade.   
 *      This includes instances where students did not upload the correct file for grading.
 *  - All labs must be submitted via the upload link on Canvas.  Labs are not accepted through 
 *      e-mail or Canvas Messenger.
 *  - Students must make a credible attempt to pass all programming labs to receive a passing
 *      grade in the course.
 *
 * All values are example values only - student programs will be evaluated with 
 * different inputs.  Students are expected to test their code with different 
 * values to ensure their code functions correctly.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

extern uint64_t add64(uint32_t x, uint32_t y); // 1. returns x + y
extern uint64_t sub64(uint64_t x, uint64_t y); // 2. returns x - y
extern int16_t minS16(int16_t x, int16_t y); // 3. returns the minimum of x, y
extern uint8_t minU8(uint8_t x, uint8_t y); // 4. returns the minimum of x, y
extern bool isLessThanU32(uint32_t x, uint32_t y); // 5. returns 1 if x < y, 0 else
extern bool isLessThanS8(int8_t x, int8_t y); // 6. returns 1 if x < y, 0 else
extern uint16_t shiftLeftU16 (uint16_t x, uint16_t p); // 7. returns x << p = x * 2^p for p = 0 .. 16
extern uint16_t shiftU16(uint16_t x, int16_t p); // 8. return x * 2^p for p = -16 .. 16
extern int8_t shiftS8(int8_t x, int8_t p); // 9. return x * 2^p for p = -8 .. 8
extern bool isEqualS16(int16_t x, int16_t y); // 10. returns 1 if x == y, 0 if x != y
extern bool isEqualU32(uint32_t x, uint32_t y); // 11. returns 1 if x == y, 0 if x != y

int main(void) {
	
	uint32_t a = 4000000000;
	uint32_t b = 3000000000;
	
	printf("Question 1, add64: Correct answer = %lld\n", 7000000000);
	printf("Question 1, add64: Student answer = %lld\n\n", add64(a, b));
	
	uint64_t c = 9000000000;
	uint64_t d = 8000000000;
	
	printf("Question 2, sub64: Correct answer = %lld\n", c - d);
	printf("Question 2, sub64: Student answer = %lld\n\n", sub64(c, d));
	
	int16_t e = 254;
	int16_t f = 4;
	
	printf("Question 3, minS16, test 1: Correct answer = %hd\n", f);
	printf("Question 3, minS16, test 1: Student answer = %hd\n\n", minS16(e, f));
	
	printf("Question 3, minS16, test 2: Correct answer = %hd\n", f);
	printf("Question 3, minS16, test 2: Student answer = %hd\n\n", minS16(f, e));
	
	uint8_t g = 8;
	uint8_t h = 42;
	
	printf("Question 4, minU8, test 1: Correct answer = %hhu\n", g);
	printf("Question 4, minU8, test 1: Student answer = %hhu\n\n", minU8(g, h));
	
	printf("Question 4, minU8, test 2: Correct answer = %hhu\n", g);
	printf("Question 4, minU8, test 2: Student answer = %hhu\n\n", minU8(h, g));
	
	uint32_t i = 32;
	uint32_t j = 16;
	
	printf("Question 5, isLessThanU32, test 1: Correct answer = %u\n", 0);
	printf("Question 5, isLessThanU32, test 1: Student answer = %u\n\n", isLessThanU32(i, j));
	
	printf("Question 5, isLessThanU32, test 2: Correct answer = %u\n", 1);
	printf("Question 5, isLessThanU32, test 2: Student answer = %u\n\n", isLessThanU32(j, i));
	
	int8_t k = -3;
	int8_t l = 2;
	
	printf("Question 6, isLessThanS8, test 1: Correct answer = %hhd\n", 1);
	printf("Question 6, isLessThanS8, test 1: Student answer = %hhd\n\n", isLessThanS8(k, l));
	
	printf("Question 6, isLessThanS8, test 2: Correct answer = %hhd\n", 0);
	printf("Question 6, isLessThanS8, test 2: Student answer = %hhd\n\n", isLessThanS8(l, k));
	
	uint16_t m = 3;
	uint16_t n = 4;
	
	printf("Question 7, shiftLeftU16: Correct answer = %hu\n", 48);
	printf("Question 7, shiftLeftU16: Student answer = %hu\n\n", shiftLeftU16(m, n));

	uint16_t m_a = 8;
	uint16_t n_a = 12;
	
	printf("Question 8, shiftU16, test 1: Correct answer = %hu\n", 32768);
	printf("Question 8, shiftU16, test 1: Student answer = %hu\n\n", shiftU16(m_a, n_a));
	
	printf("Question 8, shiftU16, test 2: Correct answer = %hu\n", 2);
	printf("Question 8, shiftU16, test 2: Student answer = %hu\n\n", shiftU16(m_a, -2));
	
	int8_t o = -4;
	int8_t p = 4;
	
	printf("Question 9, shiftS8, test 1: Correct answer = %hhd\n", -64);
	printf("Question 9, shiftS8, test 1: Student answer = %hhd\n\n", shiftS8(o, p));
	
	printf("Question 9, shiftS8, test 2: Correct answer = %hhd\n", -2);
	printf("Question 9, shiftS8, test 2: Student answer = %hhd\n\n", shiftS8(o, -1));
	
	int16_t q = -32;
	int16_t r = 16;
	
	printf("Question 10, isEqualS16, test 1: Correct answer = %hd\n", 0);
	printf("Question 10, isEqualS16, test 1: Student answer = %hd\n\n", isEqualS16(q, r));
	
	printf("Question 10, isEqualS16, test 2: Correct answer = %hd\n", 1);
	printf("Question 10, isEqualS16, test 2: Student answer = %hd\n\n", isEqualS16(q, q));
	
	uint32_t s = 32;
	uint32_t t = 16;
	
	printf("Question 11, isEqualU32, test 1: Correct answer = %u\n", 0);
	printf("Question 11, isEqualU32, test 1: Student answer = %u\n\n", isEqualU32(s, t));
	
	printf("Question 11, isEqualU32, test 2: Correct answer = %u\n", 1);
	printf("Question 11, isEqualU32, test 2: Student answer = %u\n\n", isEqualU32(s, s));
	
	return EXIT_SUCCESS;
}
