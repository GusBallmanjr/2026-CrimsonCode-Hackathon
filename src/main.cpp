#include "../include/FileWritting.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

  std::string flag1 = argv[1];
  std::string file1 = argv[2];
  std::string file2 = argv[3];
  if (flag1 == "--help") {
    std::cout << "joshua | public / private key encryption" << std::endl << "--help | prints this list" << std::endl << "-create-keys <name> | creates a set of public / private keys" << std::endl << "-encrypt <decrypted-file> <public-key> | encrypts file with public key" << std::endl << "-decrypt <encrypted-file> <private-key> | decrypts file with private key" << std::endl;
  }
  else if (flag1 == "-create-keys") {
    if (argc == 2) createKeys(file1);
    else std::cout << "\"-create-keys\" requires 1 argument" << std::endl;
  } else if (flag1 == "-encrypt") {
    if (argc == 3) { 
      std::ifstream plaintext(file1);
      std::ifstream publicKey(file2);
      encryptFile(plaintext, publicKey);
    } else {
      std::cout << "\"-encrypt\" requires two arguments" << std::endl;
    }
  } else if (flag1 == "-decrypt") {
    if (argc == 3) {
      std::ifstream encryptedFile(file1);
      std::ifstream privateKey(file2);
      decryptFile(encryptedFile, privateKey);
    } else {
      std::cout << "\"-encrypt\" requires two arguments" << std::endl;
    }
  } else {
    std::cout << "joshua requires proper arguments. See --help for more info" << std::endl;
  }

}
