/*
 *
 *  Encryption Module
 *  Authors: Jameson Scott, Gus Ballman
 *  Description: Provides modular‑arithmetic–based encryption utilities using
 *               integer-safe modular exponentiation.
 *
 */

#pragma once
#include <cstdint>
#include <iostream>

 // Cryptographic Parameters
#define P 1223
#define G 2063
#define r 18

class Encrypt
{
public:
    Encrypt();
    void encryption(int32_t p, int8_t E, int64_t* c1, int64_t* c2);

private:
    int64_t enc1();
    int64_t enc2(int32_t p, int8_t E);
};

// Integer-Safe Modular Exponentiation (Written by Copilot)
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
