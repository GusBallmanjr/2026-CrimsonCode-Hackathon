/*
 *  Encryption Module Implementation
 *  Authors: Jameson Scott, Gus Ballman
 *
 *  This file provides the implementation of the Encrypt class, including:
 *    + Construction of the encryption object
 *    + Generation of ciphertext components (c1, c2)
 *    + Internal modular‑arithmetic routines for exponentiation‑based encryption
 *
 *  The encryption process uses integer‑safe modular exponentiation to avoid
 *  precision loss and ensure deterministic behavior suitable for cryptographic
 *  experimentation and embedded systems work.
 */

#include "Encrypt.hpp"

Encrypt::Encrypt()
{
}

void Encrypt::encryption(int32_t p, int8_t E, int64_t* c1, int64_t* c2)
{
	*c1 = enc1();
	*c2 = enc2(p, E);
}

int64_t Encrypt::enc1()
{
	return modexp(G, r, P);
}

int64_t Encrypt::enc2(int32_t p, int8_t E)
{
	return p * modexp(E, r, P);
}
