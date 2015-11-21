#include "test8.h"

#include "galois_field.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

// TEST
// ( X + Y ) ^ 2 = X ^ 2 + Y ^ 2
void Test_square_identity_8()
{
	uint64_t x = rand() % 256;
	uint64_t y = rand() % 256;

	uint64_t m0 = galois_field_pow(galois_field_add(x, y), 2, POWER8);
	uint64_t m1 = galois_field_add(galois_field_pow(x, 2, POWER8), galois_field_pow(y, 2, POWER8));

	assert(m0 == m1);
}

// TEST
// ( X ) ^ ( 2 ^ 32 - 1) = 1
void Test_pow_identity_1_8()
{
	uint64_t x = rand() % 256;

	while (!x)
	{
		x = rand() % 256;
	}

	uint64_t m0 = galois_field_pow(x, MAX_FIELD_INTEGER_8 - 1, POWER8);

	assert(m0 == 1L);
}

// TEST
// X ^ n = X ^ ( n mod (2 ^ 32 - 1))
void Test_pow_identity_2_8()
{
	uint64_t x = rand() % 256;
	uint64_t n = rand() % 256;

	uint64_t m0 = galois_field_pow(x, n, POWER8);
	uint64_t m1 = galois_field_pow(x, n % (MAX_FIELD_INTEGER_8 - 1), POWER8);

	assert(m0 == m1);
}

void Test_gcd_1_8()
{
	uint64_t x = rand() % 256;
	uint64_t n = rand() % 256;
	uint64_t m = rand() % 256;

	uint64_t q = galois_field_gcd(m, n, POWER8);

	assert(galois_field_remainder(m, q, POWER8) == 0);
	assert(galois_field_remainder(n, q, POWER8) == 0);
}

void Test_generator()
{
	uint64_t a = 2;
	uint64_t GF8[ 256 ] = { 0 };

	GF8[0] = 1;

	for (size_t i = 0; i < 256; i++)
	{
		uint64_t m0 = galois_field_pow(a, i, POWER8);

		GF8[m0 % 256] = 1;
	}

	for (size_t i = 0; i < 256; i++)
	{
		assert(GF8[ i ] == 1);
	}
}

void Test_inverse_8()
{
	uint64_t n = rand() % 256;

	uint64_t c1 = galois_field_invert(n, POWER8);
	uint64_t c2 = galois_field_mul(c1, n, POWER8);

	assert(n == 0 || c2 == 1);
}
