/*
 *  Decryption Module Implementation
 *  Authors: Jameson Scott, Gus Ballman
 *
 *  Implements the operational logic of the Decrypt class, responsible for
 *  reversing the encryption process and reconstructing the original plaintext.
 *  The workflow includes:
 *
 *    + Computing the shared secret value s = c1^r mod P
 *    + Deriving the modular inverse s' using Fermat’s Little Theorem
 *    + Recovering the plaintext by combining s' with the ciphertext component c2
 *
 *  All arithmetic is performed using deterministic, integer‑safe modular
 *  exponentiation to ensure correctness and reproducibility in cryptographic
 *  experimentation and embedded systems environments.
 */

#include "Decrypt.hpp"

Decrypt::Decrypt()
{
}

int16_t Decrypt::decryption(int64_t c1, int64_t c2)
{
	int16_t p = 0;
	int64_t sValue = s(c1);
	sValue = sPrime(sValue);
	p = dec2(sValue, c2);
	return p;
}

int64_t Decrypt::s(int64_t c1)
{
    return modexp(c1, r, P);
}

int64_t Decrypt::sPrime(int64_t s)
{
	return modexp(s, (P - 2), P);
}

int16_t Decrypt::dec2(int64_t sPrime, int64_t c2)
{
	return c2 * (sPrime % P);
}
