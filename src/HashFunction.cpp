#include "../include/HashFunction.hpp"

std::string hashPassword(std::string password) {
  
  std::string returnString;
  int size = password.size();
  
  for (int i = 0; i < size; i++) {
    int x = int(password[i]) + 1;
    for (int j = 1; j < size; j++) {
      if (size % j == 0) {
        if (32 < (x * i + j) % 255 || (x * i + j) % 255 < 127) {
          returnString += (x * i + j) % 127 + 33;
        } else {
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
  int size = hash.size();
  int n = (hash[0] * hash[size - 1] + hash[size / 2]) % 255;
  if (n <= 0) return -1;
    
    int count = 0;
    int candidate = 1;

    while (count < n) {
        candidate++;
        if (isPrime(candidate)) {
            count++;
        }
    }
    return candidate;
}
