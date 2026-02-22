#include "../include/FileWritting.hpp"

void createKeys(std::string &keyName) {
  std::ofstream publicKey(keyName + "_public_key.pbk");
  std::ofstream privateKey(keyName + "_private_key.prk");
}

void encryptFile(std::ifstream &plaintext, std::ifstream &publicKey) {

}

void decryptFile(std::ifstream &encryptedText, std::ifstream &privateKey) {

}
