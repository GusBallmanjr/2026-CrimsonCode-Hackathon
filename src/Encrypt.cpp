#include "../include/Encrypt.hpp"

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

static int64_t modexp(int64_t base, int64_t exp, int64_t mod)
{
    int64_t result = 1;
    base %= mod;

    while (exp > 0)
    {
        if (exp & 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp >>= 1;
    }

    return result;
}
