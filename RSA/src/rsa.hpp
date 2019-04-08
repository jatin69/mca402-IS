#ifndef RSA_SRC_RSA_HPP
#define RSA_SRC_RSA_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long int ulli;

extern ulli p;
extern ulli q;
extern ulli n;
extern ulli r;
extern ulli e;
extern ulli d;

void generateKeys();
void encryption();
void decryption();
ulli cipher(ulli, string);

// utils
bool isPrime(ulli);
bool areCoprime(ulli, ulli);

string trimSpace(string);
string intToBinary(ulli);

#endif // !RSA_SRC_RSA_HPP