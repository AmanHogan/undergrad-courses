//Aman Hogan-Bailey MAV-ID: 1001830469//
//Coding Assignment 7//

#include <stdio.h>
#include <stdlib.h>
#include "ListLib.h"

#ifndef _FILELIB_H_
#define _FILELIB_H_

void ReadFileIntoLinkedList(FILE *DCFile, NODE** LinkedListHead);
FILE *OpenFile(int argc, char *argv[]);

#endif