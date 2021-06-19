#ifndef UTILS_H
#define UTILS_H


// Headers
#include <stdio.h>
#include <stdlib.h>

#include "types.h"


// Info Macro Function
#define info(fmt, ...) printf("INFO:\t"fmt"\n", ##__VA_ARGS__)


// Error Macro Function
#define error(fmt, ...) { \
	fprintf(stderr, "ERROR:\t"fmt"\n", ##__VA_ARGS__); \
	exit(0x01); \
}


// Random Seed Function
void randoms(uint32_t seed);


// Random Function
uint32_t random();


// Random Float Function
float randomf();


#endif