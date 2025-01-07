#include "mt19937.h"
#include <stdio.h>

static uint32_t mt[MT19937_N]; // State vector
static int mti = MT19937_N + 1;

// Initialize the MT19937 generator with a seed
void init_mt19937(uint32_t seed)
{
    mt[0] = seed;
    for (mti = 1; mti < MT19937_N; mti++)
    {
        mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        mt[mti] &= 0xffffffffUL; // Ensure 32-bit integer
    }
}

// Generate a random number on [0, 0xffffffff]-interval
uint32_t mt19937_generate()
{
    uint32_t y;
    static uint32_t mag01[2] = {0x0UL, MATRIX_A};

    if (mti >= MT19937_N)
    {
        int kk;

        if (mti == MT19937_N + 1)
            init_mt19937(5489UL); // Default seed

        for (kk = 0; kk < MT19937_N - MT19937_M; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + MT19937_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < MT19937_N - 1; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (MT19937_M - MT19937_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[MT19937_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[MT19937_N - 1] = mt[MT19937_M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

// Generate a random number in [0, 1)
double mt19937_generate_double()
{
    return mt19937_generate() * (1.0 / 4294967296.0); // Divide by 2^32
}