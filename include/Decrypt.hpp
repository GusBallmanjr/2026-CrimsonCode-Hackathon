#pragma once
#include "Encrypt.hpp"

class Decrypt
{
public:
	Decrypt();
private:
	int64_t s(int64_t c1);
	int64_t sPrime(int64_t s);
	int16_t dec2(int64_t sPrime, int64_t c2);
};
