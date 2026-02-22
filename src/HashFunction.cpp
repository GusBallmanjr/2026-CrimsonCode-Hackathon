#include "HashFunction.hpp"

std::string hashPassword(std::string password) {

    std::string returnString;
    int size = password.size();

    for (int i = 0; i < size; i++) {
        int x = int(password[i]) + 1;
        for (int j = 1; j < size; j++) {
            if (size % j == 0) {
                if (32 < (x * i + j) % 255 || (x * i + j) % 255 < 127) {
                    returnString += (x * i + j) % 127 + 33;
                }
                else {
                    returnString += char((x * i + j) % 255);
                }
            }
        }
    }

    return returnString;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int hashToPrime(std::string hash) {
    int sum = 0;

    for (char c : hash)
    {
        sum += (unsigned char)c;
    }

    sum = sum % 251;

    // never allow 0 or 1 (these cause infinite loops in EncryptFinal)
    if (sum < 2)
    {
        sum = 2;
    }

    return sum;

}

/*
int main(void) {
  std::string phrase = "Th1s1sMyV3ry!!S3cur3P@s$W0rd$g8";
  std::cout << hashPassword(phrase) << std::endl;

  std::cout << std::endl << std::endl << "Prime Number: " << hashToPrime(phrase) << std::endl;
  return 0;
}*/