// Headers
#include <stdio.h>
#include <stdlib.h>

#include "types.h"


// File Variables
static uint32_t seed;


// Random Seed Function
void randoms(uint32_t _seed) {
	seed = _seed;
}


// Random Function
uint32_t random() {
	seed ^= seed<<0x0D;
	seed ^= seed>>0x11;
	seed ^= seed<<0x05;
	return seed;
}


// Random Float Function
float randomf() {
	union {uint32_t u; float f;} x = {.f = 1.0f};
	x.u |= random()&0x7FFFFF;
	return x.f-0x01;
}