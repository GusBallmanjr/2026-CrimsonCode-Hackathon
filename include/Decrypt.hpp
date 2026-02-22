/*
 *  Decryption Module
 *  Authors: Jameson Scott, Gus Ballman
 *
 *  This header defines the Decrypt class, which performs the inverse operations
 *  required to recover plaintext from the ciphertext pair (c1, c2). The module
 *  implements:
 *
 *    + Computation of the shared secret value s = c1^r mod P
 *    + Derivation of the multiplicative inverse component s'
 *    + Final plaintext reconstruction using modular arithmetic
 *
 *  These routines complement the Encrypt module and complete the full
 *  encryption/decryption workflow using deterministic integer‑safe operations.
 */

#pragma once
#include "Encrypt.hpp"

class Decrypt
{
public:
	Decrypt();
	int16_t decryption(int64_t c1, int64_t c2);
private:
	int64_t s(int64_t c1);
	int64_t sPrime(int64_t s);
	int16_t dec2(int64_t sPrime, int64_t c2);
};