#pragma once
#include <iostream>
#include <cstdint>
#include <cmath>

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

static int64_t modexp(int64_t base, int64_t exp, int64_t mod);
