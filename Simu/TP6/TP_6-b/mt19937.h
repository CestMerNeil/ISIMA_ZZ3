#ifndef MT19937_H
#define MT19937_H

#include <stdint.h>

#define MT19937_N 624
#define MT19937_M 397
#define MATRIX_A 0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL

void init_mt19937(uint32_t seed);
uint32_t mt19937_generate();
double mt19937_generate_double();

#endif // MT19937_H