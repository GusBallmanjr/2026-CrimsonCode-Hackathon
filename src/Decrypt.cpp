#include "Decrypt.hpp"

Decrypt::Decrypt()
{
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
