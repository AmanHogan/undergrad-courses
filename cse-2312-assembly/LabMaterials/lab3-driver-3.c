/* CSE 2312 - Fall 2021 - Lab 3 Driver
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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 32
#define COUNT 3

typedef struct _BUSINESS {
	uint32_t taxId;
	char name[MAX_NAME_LENGTH + 1];
	uint32_t addNo;
	char direction;
	char street[MAX_NAME_LENGTH + 1];
	char city[MAX_NAME_LENGTH + 1];
	char state[2 + 1];
	uint32_t zip;
} BUSINESS;

extern void sortDecendingInPlace (int8_t x[], uint32_t count);
extern float sumF32(float x[], uint32_t count);
extern float prodF32(float x[], uint32_t count);
extern double dotpF64(double x[], double y[], uint32_t count);
extern float maxF32(float x[], uint32_t count);
extern double absSumF64 (double x[], uint32_t count);
extern double sqrtSumF64(double x[], uint32_t count);
extern char getDirection (BUSINESS business[], uint32_t index);
extern uint32_t getAddNo (BUSINESS business[], uint32_t index);
extern char * getCity(BUSINESS business[], uint32_t index);

int main(void) {
	BUSINESS business[COUNT] = {
	        {12342332, "Home Depot", 201, 'W', "Road to Six Flags", "Arlington", "TX", 76011},
	        {18091123, "Kroger", 945, 'W', "Lamar Blvd", "Dallas", "TX", 76012},
	        {81927322, "Round1", 3811, 'S', "Cooper St", "Irving", "TX", 76015} 
	};
	

	float fArray [COUNT] = {2.2, -1.2, -3.2};
	double dArray [COUNT] = {2.1, 1.1, 3.1};
	double dArray_y[COUNT] = {3.1, 4.1, 5.1};
	
	printf("Question 1, sumF32: Correct answer = -2.2\n");
	printf("Question 1, sumF32: Student answer = %.1f\n\n", sumF32(fArray, COUNT));
	
	printf("Question 2, prodF32: Correct answer = 8.448\n");
	printf("Question 2, prodF32: Student answer = %.3f\n\n", prodF32(fArray, COUNT));
	
	printf("Question 3, dotpF64: Correct answer = 26.83\n");
	printf("Question 3, dotpF64: Student answer = %.2lf\n\n", dotpF64(dArray, dArray_y, COUNT));
	
	printf("Question 4, maxF32: Correct answer = 2.2\n");
	printf("Question 4, maxF32: Student answer = %.1lf\n\n", maxF32(fArray, COUNT));
	
	dArray[0] = -8.1;
	
	printf("Question 5, absSumF64: Correct answer = 3.9\n");
	printf("Question 5, absSumF64: Student answer = %.1lf\n\n", absSumF64(dArray, COUNT));
	
	dArray[0] = 6.2;
	
	printf("Question 6, sqrtSumF64: Correct answer = 3.225\n");
	printf("Question 6, sqrtSumF64: Student answer = %.3lf\n\n", sqrtSumF64(dArray, COUNT));

	printf("Question 7, getDirection: Correct answer = W\n");
	printf("Question 7, getDirection: Student answer = %c\n\n", getDirection(business, 0));
	
	printf("Question 8, getAddNo: Correct answer = 945\n");
	printf("Question 8, getAddNo: Student answer = %u\n\n", getAddNo(business, 1));
	
	printf("Question 9, getCity: Correct answer = Irving\n");
	printf("Question 9, getCity: Student answer = %s\n\n", getCity(business, 2));
	
	printf("Bonus, sortDecendingInPlace: Correct answer = 5  2  -3\n");
	
	int8_t i8Array [COUNT] = {5, -3, 2};
	uint32_t i = 0;
	sortDecendingInPlace(i8Array, COUNT);
	
	printf("Bonus, sortDecendingInPlace: Student Answer = ");
	for(i = 0; i < COUNT; i++) {
			printf("%hhd  ", i8Array[i]);
	}
	printf("\n");

}
