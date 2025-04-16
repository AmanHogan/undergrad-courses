#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 32

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

extern char* getName(BUSINESS business[], uint32_t index);
extern uint32_t getZip(BUSINESS business[], uint32_t index);

#define COUNT 3

int main(void) {
	uint32_t i;
	BUSINESS business[COUNT] = {
	        {12342332, "Home Depot", 201, 'W', "Road to Six Flags", "Arlington", "TX", 76011},
	        {18091123, "Kroger", 945, 'W', "Lamar Blvd", "Arlington", "TX", 76012},
	        {81927322, "Round1", 3811, 'S', "Cooper St", "Arlington", "TX", 76015} 
	};

	printf("Addresses of selected record entries:\r\n");
	char format[] = {"%p %s\r\n"};

	printf(format, &business[0], "business[0]");
	printf(format, &business[0].taxId, "taxId");
	printf(format, &business[0].name, "name");
	printf(format, &business[0].addNo, "addNo");
	printf(format, &business[0].direction, "direction");
	printf(format, &business[0].street, "street");
	printf(format, &business[0].city, "city");
	printf(format, &business[0].state, "state");
	printf(format, &business[0].zip, "zip");
	printf(format, &business[1], "business[1]");
	printf(format, &business[2], "business[2]");
	printf("\n");

	printf("Record number: ");
	scanf("%u", &i);
	printf("Name = %s\r\n", getName(business, i));
	printf("ZIP  = %u\r\n", getZip(business, i));
	return EXIT_SUCCESS;
}

