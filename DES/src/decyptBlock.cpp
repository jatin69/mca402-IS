#include "./des.hpp"

/*
Decryption is the same as Encryption
but subkeys are used in opposite order.
*/
void Des::decryptBlock() {

  int i, round;
    IP();
    for (i = 0; i < 64; i++)
      total[i] = ip[i];
    for (i = 0; i < 32; i++)
      left[i] = total[i];
    for (; i < 64; i++)
      right[i - 32] = total[i];

    for (round = 1; round <= 16; round++) {
      expandMsg();
      xor_one_decryption(round);
      substitution();
      permutation();
      xor_sides();
      for (i = 0; i < 32; i++)
        left[i] = right[i];
      for (i = 0; i < 32; i++)
        right[i] = xor2[i];
    }

    for (i = 0; i < 32; i++)
      temp[i] = right[i];
    for (; i < 64; i++)
      temp[i] = left[i - 32];

    inverseIP();
}

/*In decryption, subkeys order are opposite
*/
void Des::xor_one_decryption(int round) {
  int i;
  for (i = 0; i < 48; i++)
    xor1[i] = expansion[i] ^ keyi[16 - round][i];
}
