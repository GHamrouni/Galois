#include "test32.h"

#include "galois_field.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

// TEST
// ( X + Y ) ^ 2 = X ^ 2 + Y ^ 2
void Test_square_identity()
{
	uint64_t x = rand();
	uint64_t y = rand();

	uint64_t m0 = galois_field_pow(galois_field_add(x, y), 2, POWER32);
	uint64_t m1 = galois_field_add(galois_field_pow(x, 2, POWER32), galois_field_pow(y, 2, POWER32));

	assert(m0 == m1);
}

// TEST
// ( X ) ^ ( 2 ^ 32 - 1) = 1
void Test_pow_identity_1()
{
	uint64_t x = rand();
	uint64_t m0 = galois_field_pow(x, MAX_FIELD_INTEGER_32 - 1, POWER32);

	assert(m0 == 1L);
}

// TEST
// X ^ n = X ^ ( n mod (2 ^ 32 - 1))
void Test_pow_identity_2()
{
	uint64_t x = rand();
	uint64_t n = rand();

	uint64_t m0 = galois_field_pow(x, n, POWER32);
	uint64_t m1 = galois_field_pow(x, n % (MAX_FIELD_INTEGER_32 - 1), POWER32);

	assert(m0 == m1);
}

void Test_gcd_1()
{
	uint64_t x = rand();
	uint64_t n = rand();
	uint64_t m = rand();

	uint64_t q = galois_field_gcd(m, n, POWER32);

	assert(galois_field_remainder(m, q, POWER32) == 0);
	assert(galois_field_remainder(n, q, POWER32) == 0);
}

void Test_inverse()
{
	uint64_t n = rand();

	uint64_t c1 = galois_field_invert(n, POWER32);
	uint64_t c2 = galois_field_mul(c1, n, POWER32);

	assert(n == 0 || c2 == 1);
}