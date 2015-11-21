/********************************************************************/
/*          test32.h                                                */
/*            Tests for Galois Field GF(2^32)		                */
/*                                                                  */
/*          Ghassen Hamrouni 29-08-2015                             */
/********************************************************************/

#ifndef	_GALOIS_FIELD_TEST_HC_H
#define	_GALOIS_FIELD_TEST_HC_H

#ifdef __cplusplus
extern "C" {
#endif

	// TEST
	// ( X + Y ) ^ 2 = X ^ 2 + Y ^ 2
	void Test_square_identity();

	// TEST
	// ( X ) ^ ( 2 ^ 32 - 1) = 1
	void Test_pow_identity_1();

	// TEST
	// X ^ n = X ^ ( n mod (2 ^ 32 - 1))
	void Test_pow_identity_2();

	void Test_gcd_1();

	// TEST
	// Test the multiplicative inverse
	void Test_inverse();

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif // _GALOIS_FIELD_TEST_HC_H
