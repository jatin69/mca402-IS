#include "./des.hpp"

/*
Decryption is the same as Encryption
but subkeys are used in opposite order.
*/
char *Des::Decrypt(char *Text1) {

  int i, a1, j, nB, m, iB, k, K, B[8], n, t, d, round;

  // generate all required keys - same as encryption
  keygen();

  // making copy for safety
  char *Text = new char[1000];
  strcpy(Text, Text1);

  unsigned char ch;

  // Unlike encryption, message will always be multiple of 8, as it comes to us
  // after encryption
  i = strlen(Text);
  int mc = 0;

  for (iB = 0, nB = 0, m = 0; m < (strlen(Text) / 8); m++) {
    for (iB = 0, i = 0; i < 8; i++, nB++) {
      ch = Text[nB];
      n = (int)ch;
      for (K = 7; n >= 1; K--) {
        B[K] = n % 2;
        n /= 2;
      }
      for (; K >= 0; K--)
        B[K] = 0;
      for (K = 0; K < 8; K++, iB++)
        total[iB] = B[K];
    }

    IP();
    for (i = 0; i < 64; i++)
      total[i] = ip[i];
    for (i = 0; i < 32; i++)
      left[i] = total[i];
    for (; i < 64; i++)
      right[i - 32] = total[i];

    for (round = 1; round <= 16; round++) {
      Expansion();
      xor_oneD(round);
      substitution();
      permutation();
      xor_two();
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
    for (i = 0; i < 8; i++) {
      k = 128;
      d = 0;
      for (j = 0; j < 8; j++) {
        d = d + inv[i][j] * k;
        k = k / 2;
      }
      final[mc++] = (char)d;
    }
  }
  final[mc] = '\0';

  char *final1 = new char[1000];
  for (i = 0, j = strlen(Text); i < strlen(Text); i++, j++)
    final1[i] = final[j];
  final1[i] = '\0';
  return (final);
}

/*In decryption, subkeys order are opposite
*/
void Des::xor_oneD(int round) {
  int i;
  for (i = 0; i < 48; i++)
    xor1[i] = expansion[i] ^ keyi[16 - round][i];
}
