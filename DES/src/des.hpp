#ifndef DES_SRC_DES_HPP
#define DES_SRC_DES_HPP

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

extern int key[64];

class Des {
public:
  int keyi[16][48], total[64], left[32], right[32], ck[28], dk[28],
      expansion[48], z[48], xor1[48], sub[32], p[32], xor2[32], temp[64],
      pc1[56], ip[64], inv[8][8];

  char final[1000];

  void IP();
  void inverseIP();

  void Expansion();
  void substitution();
  void permutation();

  void keygen();
  void PermChoice1();
  void PermChoice2();

  char *Encrypt(char *);
  char *Decrypt(char *);

  void xor_two();
  void xor_oneE(int);
  void xor_oneD(int);
};

#endif // !DES_SRC_DES_HPP
