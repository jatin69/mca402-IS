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

  char finalStr[1000];

  void IP();
  void inverseIP();

  void expandMsg();
  void substitution();
  void permutation();

  void keygen();
  void applyPC1();
  void applyPC2();

  void encryptBlock();
  void decryptBlock();

  void xor_sides();
  void xor_one_encryption(int);
  void xor_one_decryption(int);

  char* mode_ECB_encrypt(char *);
  char* mode_ECB_decrypt(char *);

  char* mode_CBC_encrypt(char *);
  char* mode_CBC_decrypt(char *);
  
  char* mode_CFB_encrypt(char *);
  char* mode_CFB_decrypt(char *);

  char* mode_OFB_encrypt(char *);
  char* mode_OFB_decrypt(char *);

  char* mode_CTR_encrypt(char *);
  char* mode_CTR_decrypt(char *);
};

#endif // !DES_SRC_DES_HPP
