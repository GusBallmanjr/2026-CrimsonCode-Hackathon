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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>
#include <fstream>
#include "Encrypt.hpp"
#include "Decrypt.hpp"

extern int32_t Primes[256];

typedef enum enDe
{
	NEITHER = 0, ENCRYPT = 1, DECRYPT = 2
}EnDe;

int16_t GenerateD();
int16_t generateE(int16_t D, int16_t N);
char bin2hex(uint8_t binary);
void BinaryHexMultiple(int64_t binary, std::string hex);
int32_t mapping(int Primes[256], char plaintext, int offset);
char inverseMapping(int Primes[256], int32_t p, int offset);
void EncryptFinal(std::string filename, int offset, int16_t E);
void DecryptFinal(std::string filename, int offset);