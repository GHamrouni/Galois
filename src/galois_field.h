/********************************************************************/
/*    galois_field.h                                                */
/*        Galois Field (2^8) & GF(2^32)		                        */
/*        Galois field arithmetic in a characteristic 2 field       */
/*                                                                  */
/*    @author Ghassen Hamrouni (ghamrouni@iptech-group.com)         */
/*    @date 2015/08/30                                              */
/********************************************************************/

#ifndef	_GALOIS_FIELD_HC_H
#define	_GALOIS_FIELD_HC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

	// MAX_FIELD_INTEGER_32 = 2 ^ 32
	#define MAX_FIELD_INTEGER_32	(0x100000000L)

	// MAX_FIELD_INTEGER_8	= 2 ^ 8
	#define MAX_FIELD_INTEGER_8		(0x100L)

	typedef enum
	{
		POWER8,
		POWER32
	} GaloisFieldPrimePower;

	uint64_t galois_field_add(uint64_t m, uint64_t n);

	uint64_t galois_field_sub(uint64_t m, uint64_t n);

	uint64_t galois_field_mul(uint64_t x, uint64_t y, GaloisFieldPrimePower w);

	uint64_t galois_field_pow(uint64_t x, uint64_t n, GaloisFieldPrimePower w);

	uint64_t galois_field_div(uint64_t a, uint64_t b, uint64_t* q, uint64_t* r, GaloisFieldPrimePower w);

	uint64_t galois_field_remainder(uint64_t a, uint64_t b, GaloisFieldPrimePower w);

	// Multiplicative inverse by the extended GCD algorithm
	uint64_t galois_field_invert(uint64_t a, GaloisFieldPrimePower w);

	// Standard euclidean division without modular arithmetic
	void galois_field_ediv(uint64_t a, uint64_t b, uint64_t *q, uint64_t *r, GaloisFieldPrimePower w);

	// Euclid's GCD algorithm
	uint64_t galois_field_gcd(uint64_t a, uint64_t b, GaloisFieldPrimePower w);

	// The degree of the binary polynomial
	int		 galois_degree(uint64_t x, GaloisFieldPrimePower w);

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif // _GALOIS_FIELD_HC_H
