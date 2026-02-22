#include <fstream>
#include <string>

void createKeys(std::string &keyName);

void encryptFile(std::ifstream &plaintext, std::ifstream &publicKey);

void decryptFile(std::ifstream &encryptedText, std::ifstream &privateKey);
