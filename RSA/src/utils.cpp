#include "./rsa.hpp"

bool isPrime(ulli x) {
  if (x <= 1)
    return false;
  for (ulli i = 2; i <= sqrt(x); i++) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

bool areCoprime(ulli x, ulli y) {
  for (ulli i = 2; i <= sqrt(min(x, y)); i++) {
    if (x % i == 0 && y % i == 0)
      return false;
  }
  return true;
}

string trimSpace(string s) {
  while (s.at(0) == ' ') {
    s = s.substr(1, s.length() - 1);
  }
  while (s.at(s.length() - 1) == ' ') {
    s = s.substr(0, s.length() - 1);
  }

  return s;
}

string intToBinary(ulli a) {
  string b = "";
  while (a != 0) {
    if (a % 2 == 1)
      b = "1" + b;
    else
      b = "0" + b;

    a /= 2;
  }
  return b;
}
