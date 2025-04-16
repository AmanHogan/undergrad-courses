#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 32

typedef struct _BUSINESS {
	uint32_t taxId;
	char name[MAX_NAME_LENGTH+1];
	uint32_t addNo;
	char direction;
	char street[MAX_NAME_LENGTH+1];
	char city[MAX_NAME_LENGTH+1];
	char state[2+1];
	uint32_t zip;
} BUSINESS;

extern char * getName(BUSINESS * business);
extern uint32_t getZip(BUSINESS * business);

int main() {
	uint32_t i;
	BUSINESS business = {12342332, "Home Depot", 201, 'W', "Road to Six Flags", "Arlington", "TX", 76011};

	char format[] = {"%p %s\r\n"};
	printf(format, &business, "business");
	printf(format, &business.taxId, "taxId");
	printf(format, &business.name, "name");
	printf(format, &business.addNo, "addNo");
	printf(format, &business.direction, "direction");
	printf(format, &business.street, "street");
	printf(format, &business.city, "city");
	printf(format, &business.state, "state");
	printf(format, &business.zip, "zip");

	printf("\n");
 	printf("Name = %s\n", getName(&business));
	printf("ZIP  = %u\n", getZip(&business));
    return EXIT_SUCCESS;
}

