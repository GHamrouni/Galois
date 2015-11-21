#include "galois_field.h"

#include <stdint.h>

// 1 + x ^ 10 + x ^ 30 + x ^ 31 + x ^ 32
#define PRIME_POLY_32		(7516193793L)	

#define PRIME_POLY_8		(369L)	

uint64_t galois_field_add(uint64_t m, uint64_t n)
{
	return m ^ n;
}

uint64_t galois_field_sub(uint64_t m, uint64_t n)
{
	return m ^ n;
}

uint64_t galois_field_mod(uint64_t x, GaloisFieldPrimePower w)
{
	uint64_t m = MAX_FIELD_INTEGER_32;
	uint64_t p = PRIME_POLY_32;

	if (w == POWER8)
	{
		m = MAX_FIELD_INTEGER_8;
		p = PRIME_POLY_8;
	}

	while (x & m)
	{
		x = galois_field_sub(x, p);
	}

	return x;
}

uint64_t poly_mul(uint64_t x, uint64_t y, GaloisFieldPrimePower w)
{
	uint64_t z = 0;
	size_t nbit = 32;

	if (w == POWER8)
	{
		nbit = 8;
	}

	for (size_t i = 0; i <= nbit; i++)
	{
		if (1L & y)
		{
			z = galois_field_add(z, x);
		}

		x = x << 1L;
		y = y >> 1L;
	}

	return z;
}

int galois_degree(uint64_t x, GaloisFieldPrimePower w)
{
	int nbit = 32;
	int n = 0;

	if (w == POWER8)
	{
		nbit = 8;
	}

	for (int i = 0; i <= nbit; i++)
	{
		if (1L & x)
		{
			n = i;
		}

		x = x >> 1L;
	}

	return n;
}

void g_swap(uint64_t* a, uint64_t* b)
{
	uint64_t t = *a;

	*a = *b;
	*b = t;
}

//  Extended GCD algorithm
uint64_t galois_field_invert(uint64_t b, GaloisFieldPrimePower w)
{
	uint64_t p = PRIME_POLY_32;

	if (w == POWER8)
	{
		p = PRIME_POLY_8;
	}

	uint64_t r0 = p;
	uint64_t r1 = b;

	uint64_t s0 = 1;
	uint64_t s1 = 0;

	uint64_t t0 = 0;
	uint64_t t1 = 1;

	uint64_t t_ = 0;

	uint64_t r, q;

	while (r1 > 0)
	{
		galois_field_ediv(r0, r1, &q, &r, w);

		t_ = r1;
		r1 = galois_field_sub(r0, poly_mul(q, r1, w));
		r0 = t_;

		t_ = s1;
		s1 = galois_field_sub(s0, poly_mul(q, s1, w));
		s0 = t_;

		t_ = t1;
		t1 = galois_field_sub(t0, poly_mul(q, t1, w));
		t0 = t_;
	}

	return galois_field_mod(t0, w);
}

uint64_t galois_field_remainder(uint64_t a, uint64_t b, GaloisFieldPrimePower w)
{
	a = galois_field_mod(a, w);
	b = galois_field_mod(b, w);

	uint64_t q = 0;
	uint64_t c = 0;
	uint64_t r = a;

	int db = galois_degree(b, w);
	int dr = galois_degree(r, w);

	while (dr >= db)
	{
		c = INT64_C(1) << (dr - db);

		q = galois_field_add(c, q);
		r = galois_field_sub(r, poly_mul(c, b, w));

		dr = galois_degree(r, w);

		if (r == 0L) break;
	}

	return r;
}

uint64_t galois_field_gcd(uint64_t a, uint64_t b, GaloisFieldPrimePower w)
{
	a = galois_field_mod(a, w);
	b = galois_field_mod(b, w);

	while (1)
	{
		if (b == 0L)
		{
			return a;
		}

		a = galois_field_remainder(a, b, w);

		if (a == 0L)
		{
			return b;
		}

		b = galois_field_remainder(b, a, w);
	}
}

uint64_t galois_field_div(uint64_t a, uint64_t b, uint64_t* q, uint64_t* r, GaloisFieldPrimePower w)
{
	a = galois_field_mod(a, w);
	b = galois_field_mod(b, w);

	*q = 0;
	uint64_t c = 0;
	*r = a;

	int db = galois_degree(b, w);
	int dr = galois_degree(*r, w);

	while (dr >= db)
	{
		c = INT64_C(1) << (dr - db);

		*q = galois_field_add(c, *q);
		*r = galois_field_sub(*r, poly_mul(c, b, w));

		dr = galois_degree(*r, w);

		if (*r == 0L) break;
	}

	return *r;
}

void galois_field_ediv(uint64_t a, uint64_t b, uint64_t *q, uint64_t *r, GaloisFieldPrimePower w)
{
	*q = 0;
	uint64_t c = 0;
	*r = a;

	int db = galois_degree(b, w);
	int dr = galois_degree(*r, w);

	while (dr >= db)
	{
		c = INT64_C(1) << (dr - db);

		*q = galois_field_add(c, *q);
		*r = galois_field_sub(*r, poly_mul(c, b, w));

		dr = galois_degree(*r, w);

		if (*r == 0L) break;
	}
}

//  Implementation of Extended GCD algorithm
uint64_t galois_field_egcd(uint64_t a, uint64_t b, GaloisFieldPrimePower w)
{
	uint64_t r0 = a;
	uint64_t r1 = b;

	uint64_t s0 = 1;
	uint64_t s1 = 0;

	uint64_t t0 = 0;
	uint64_t t1 = 1;

	uint64_t t_ = 0;

	uint64_t r, q;

	while (r1 > 0)
	{
		galois_field_ediv(r0, r1, &q, &r, w);

		t_ = r1;
		r1 = galois_field_sub(r0, poly_mul(q, r1, w));
		r0 = t_;

		t_ = s1;
		s1 = galois_field_sub(s0, poly_mul(q, s1, w));
		s0 = t_;

		t_ = t1;
		t1 = galois_field_sub(t0, poly_mul(q, t1, w));
		t0 = t_;
	}

	return r0;
}

uint64_t galois_field_mul(uint64_t x, uint64_t y, GaloisFieldPrimePower w)
{
	uint64_t z = 0;

	x = galois_field_mod(x, w);
	y = galois_field_mod(y, w);

	size_t nbit = 32;

	if (w == POWER8)
	{
		nbit = 8;
	}

	for (size_t i = 0; i < nbit; i++)
	{
		if (1L & y)
		{
			z = galois_field_add(z, x);
		}

		x = x << 1L;
		y = y >> 1L;

		x = galois_field_mod(x, w);
		y = galois_field_mod(y, w);
		z = galois_field_mod(z, w);
	}

	return z;
}

uint64_t galois_field_pow(uint64_t x, uint64_t n, GaloisFieldPrimePower w)
{
	if (n == 0)
	{
		return 1L;
	}

	uint64_t y = 1L;
	x = galois_field_mod(x, w);

	while (n > 1L)
	{
		if (n % 2L == 0)
		{
			x = galois_field_mul(x, x, w);
			n = n / 2L;
		}
		else
		{
			y = galois_field_mul(x, y, w);
			x = galois_field_mul(x, x, w);
			n = (n - 1L) / 2L;
		}

		x = galois_field_mod(x, w);
		y = galois_field_mod(y, w);
	}

	return galois_field_mul(x, y, w);
}
