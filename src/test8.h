/********************************************************************/
/*          test32.h                                                */
/*            Tests for Galois Field GF(2^8)		                */
/*                                                                  */
/*          Ghassen Hamrouni 29-08-2015                             */
/********************************************************************/

#ifndef	_GALOIS_FIELD_TEST_8_HC_H
#define	_GALOIS_FIELD_TEST_8_HC_H

#ifdef __cplusplus
extern "C" {
#endif

	// TEST
	// ( X + Y ) ^ 2 = X ^ 2 + Y ^ 2
	void Test_square_identity_8();

	// TEST
	// ( X ) ^ ( 2 ^ 8 - 1) = 1
	void Test_pow_identity_1_8();

	// TEST
	// X ^ n = X ^ ( n mod (2 ^ 8 - 1))
	void Test_pow_identity_2_8();

	void Test_gcd_1_8();

	void Test_generator();

	void Test_inverse_8();

#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif // _GALOIS_FIELD_TEST_8_HC_H
