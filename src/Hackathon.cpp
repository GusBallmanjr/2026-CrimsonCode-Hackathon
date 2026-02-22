#include "Hackathon.hpp"

int32_t Primes[256] =
{
      2,     3,     5,     7,    11,    13,    17,    19,
     23,    29,    31,    37,    41,    43,    47,    53,
     59,    61,    67,    71,    73,    79,    83,    89,
     97,   101,   103,   107,   109,   113,   127,   131,
    137,   139,   149,   151,   157,   163,   167,   173,
    179,   181,   191,   193,   197,   199,   211,   223,
    227,   229,   233,   239,   241,   251,   257,   263,
    269,   271,   277,   281,   283,   293,   307,   311,
    313,   317,   331,   337,   347,   349,   353,   359,
    367,   373,   379,   383,   389,   397,   401,   409,
    419,   421,   431,   433,   439,   443,   449,   457,
    461,   463,   467,   479,   487,   491,   499,   503,
    509,   521,   523,   541,   547,   557,   563,   569,
    571,   577,   587,   593,   599,   601,   607,   613,
    617,   619,   631,   641,   643,   647,   653,   659,
    661,   673,   677,   683,   691,   701,   709,   719,
    727,   733,   739,   743,   751,   757,   761,   769,
    773,   787,   797,   809,   811,   821,   823,   827,
    829,   839,   853,   857,   859,   863,   877,   881,
    883,   887,   907,   911,   919,   929,   937,   941,
    947,   953,   967,   971,   977,   983,   991,   997,
   1009,  1013,  1019,  1021,  1031,  1033,  1039,  1049,
   1051,  1061,  1063,  1069,  1087,  1091,  1093,  1097,
   1103,  1109,  1117,  1123,  1129,  1151,  1153,  1163,
   1171,  1181,  1187,  1193,  1201,  1213,  1217,  1223,
   1229,  1231,  1237,  1249,  1259,  1277,  1279,  1283,
   1289,  1291,  1297,  1301,  1303,  1307,  1319,  1321,
   1327,  1361,  1367,  1373,  1381,  1399,  1409,  1423,
   1427,  1429,  1433,  1439,  1447,  1451,  1453,  1459,
   1471,  1481,  1483,  1487,  1489,  1493,  1499,  1511,
   1523,  1531,  1543,  1549,  1553,  1559,  1567,  1571,
   1579,  1583,  1597,  1601,  1607,  1609,  1613,  1619
};

int16_t GenerateD()
{
    int16_t D = static_cast<int16_t>(rand() % 32768);

    std::ofstream out("private.key", std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<char*>(&D), sizeof(D));
    out.close();

    return D;
}

int16_t generateE(int16_t D, int16_t N)
{
    int exponent = D % N;
    return modexp(G, exponent, P);
}

char bin2hex(uint8_t binary)
{
    binary &= 0x0F;

    switch (binary)
    {
    case 0x0: return '0';
    case 0x1: return '1';
    case 0x2: return '2';
    case 0x3: return '3';
    case 0x4: return '4';
    case 0x5: return '5';
    case 0x6: return '6';
    case 0x7: return '7';
    case 0x8: return '8';
    case 0x9: return '9';
    case 0xA: return 'A';
    case 0xB: return 'B';
    case 0xC: return 'C';
    case 0xD: return 'D';
    case 0xE: return 'E';
    case 0xF: return 'F';
    }
}

void BinaryHexMultiple(int64_t binary, std::string hex)
{
    uint8_t nibble = 0;
    for (int i = 0; i < 16; i++)
    {
        int shift = (15 - i) * 4;      // start from MSB nibble
        nibble = (binary >> shift) & 0xF;
        hex[i] = bin2hex(nibble);
    }
}

int32_t mapping(int32_t Primes[256], char plaintext, int offset)
{
	int asciiValue = static_cast<int>(plaintext);
	return Primes[(asciiValue + offset)];
}

char inverseMapping(int32_t Primes[256], int32_t p, int offset)
{
    char plaintext = '\0';
	for (int i = 0; i < 256; i++)
	{
		if (Primes[i] == p)
		{
			int asciiValue = (i - offset) % 256;
			plaintext = static_cast<char>(asciiValue);
			break;
		}
	}
	return plaintext;
}

void EncryptFinal(std::string filename, int offset, int16_t E)
{
    // Read entire file into memory
    std::ifstream in(filename, std::ios::binary);
    std::string fileData((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    in.close();

    // Prepare ciphertext buffer
    std::string cipherText = "";
    cipherText.reserve(fileData.size() * 17); // each char → 1 hex + 16 hex

    // Encrypt each character in the file
    for (char ch : fileData)
    {
        char cipherTextC1 = '\0';
        int32_t mapped = mapping(Primes, ch, offset); // Maps plaintext to prime number

        Encrypt encryptor;
        int64_t c1, c2;
        encryptor.encryption(mapped, E, &c1, &c2); // takes prime and turns it into ciphertext components

        cipherTextC1 = bin2hex(c1);
        cipherText.push_back(cipherTextC1);

        char hex16[16];
        BinaryHexMultiple(c2, hex16);
        cipherText.append(hex16, 16);
    }

    // Clear file and write ciphertext
    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    out << cipherText;
}

void DecryptFinal(std::string filename, int offset)
{
    int16_t D = 0;
    std::ifstream din("private.key", std::ios::binary);
    din.read(reinterpret_cast<char*>(&D), sizeof(D));
    din.close();

    std::ifstream in(filename, std::ios::binary);
    std::string cipherText((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    in.close();

    std::string plainText = "";

    for (int i = 0; i < cipherText.size(); i += 17)
    {
        char c1Hex = cipherText[i];

        int64_t c1 = 0;
        if (c1Hex >= '0' && c1Hex <= '9') c1 = c1Hex - '0';
        else c1 = 10 + (c1Hex - 'A');

        int64_t c2 = 0;
        for (int j = 0; j < 16; j++)
        {
            char h = cipherText[i + 1 + j];
            int v = (h >= '0' && h <= '9') ? (h - '0') : (10 + (h - 'A'));
            c2 = (c2 << 4) | v;
        }

        Decrypt decryptor;
        int16_t mapped = decryptor.decryption(c1, c2);

        char plain = inverseMapping(Primes, mapped, offset);

        plainText.push_back(plain);
    }

    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
    out << plainText;
}