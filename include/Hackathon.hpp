/*
 *  Utility & Cryptographic Support Functions
 *  Authors: Jameson Scott, Gus Ballman
 *
 *  This file provides helper routines used across the encryption/decryption
 *  workflow and the surrounding application logic. It includes:
 *
 *    + generateE(): derives the public value E (Part of Public Key) using modular
 *      exponentiation with integer‑safe arithmetic.
 *
 *    + bin2hex(uint8_t): converts a 4‑bit nibble into its hexadecimal
 *      character representation, suitable for debugging, display, or
 *      serialization.
 *
 *    + bin2hex(int64_t, char[16]): expands a 64‑bit integer into a fixed
 *      16‑character hexadecimal string by extracting each nibble from
 *      most‑significant to least‑significant order.
 *
 *  These utilities support SFML‑based UI components, Windows drag‑and‑drop
 *  integration, and the cryptographic modules Encrypt and Decrypt. All
 *  operations are deterministic and avoid floating‑point math to maintain
 *  correctness in embedded and cryptographic contexts.
 */

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>
#include "Encrypt.hpp"
#include "Decrypt.hpp"

int8_t generateE(int8_t D, int8_t N)
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

void bin2hex(int64_t binary, char hex[16])
{
    uint8_t nibble = 0;
    for (int i = 0; i < 16; i++)
    {
        int shift = (15 - i) * 4;      // start from MSB nibble
        nibble = (binary >> shift) & 0xF;
        hex[i] = bin2hex(nibble);
    }
}
