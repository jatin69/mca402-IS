#include "./des.hpp"

char *Des::Encrypt(char *Text1) {
  /* creating a copy to perform operations on */
  char *Text = new char[1000];
  char *OmsgHEX = new char[1000];
  int Omsgi = -1;
  char *EmsgHEX = new char[1000];
  int Emsgi = -1;
  strcpy(Text, Text1);

  /* Generate all the required keys
  * The DES is gonna run multiple times to be able to encrypt entire message,
  * so it is logical to generate and store all keys at once.
  */
  keygen();

  int i, a1, j, nB, m, iB, k, K, B[8], n, t, d, round;

  /* Encryption condition: message length should be multiple of eight(64 bits
  * encypted at once),
  *if not multiple of eight, 0 is appended to make it multiple of 8.
  *for eg -
  *let message length is 15. It can be divided into 2 message blocks (8+7), DES
  * needs to be run 2 times.
  *In second block 0 needs to be appended in the HEXA code of plaintext to make
  *it
  * multiple of 8.
  */
  int messageBlocks = ceil(strlen(Text) / 8.0);

  /*
  * A DES run has 16 cycles. In a complete run it can encrypt 64 bits (8
  * characters of 8 bit each)
  * The entire message is broken into groups of 8 characters,
  * then DES is RUN on those 8 characters.
  */
  int encryptedMsgIndex = -1; // acts as index for final   encrypted message
  int msgIndex = -1;          // acts as index for initial plaintext message
  int binaryIndex;
  for (m = 0; m < messageBlocks; m++) {

    /* Converting group of 8-char to binary */
    binaryIndex = -1;
    for (i = 0; i < 8; i++) {
      // convert char to Ascii and then to Binary
      n = (int)Text[++msgIndex];
      K = -1;
      while (n) {
        B[++K] = n % 2;
        n /= 2;
      }
      while (K < 8) {
        B[++K] = 0;
      }
      /* store in reverse order,
      as, after conversion, binary is always read upside down.
      */
      for (K = 7; K >= 0; K--) {
        total[++binaryIndex] = B[K];
      }
    }
    //  cout<<"\nBinary index is : "<<binaryIndex<<" ok \n";
    /* if string is not a multiple of 8, append 0 in HEXA */
    while (binaryIndex != 63)
      total[++binaryIndex] = 0;

    /* Storing Plaintext message as HEX
     */
    int sssk = 0;
    for (i = 0; i < binaryIndex; i = i + 4) {
      sssk =
          total[i] * 8 + total[i + 1] * 4 + total[i + 2] * 2 + total[i + 3] * 1;
      if (sssk <= 9) {
        OmsgHEX[++Omsgi] = (char)(sssk + 48);
      } else {
        OmsgHEX[++Omsgi] = (char)(sssk + 87);
      }
    }
    /**/

    /* Initial permutation
     * Runs on the message, total[], to give IP
     */
    IP();
    /* copying back updated contents from IP[] to total[] */
    for (i = 0; i < 64; i++)
      total[i] = ip[i];

    /* IP is to L0 and R0*/
    for (i = 0; i < 32; i++)
      left[i] = total[i];
    for (i = 32; i < 64; i++)
      right[i - 32] = total[i];

    /* 16 Cycles of DES
     */
    for (round = 1; round <= 16; round++) {
      /* here, the drives are LEFT(n-1) and RIGHT(n-1) */
      Expansion();     /** Convert 32-bit message to 48 bit message using E-bit
                          Selection table  */
      xor_oneE(round); /** Xor the expanded right half with key (48 bits XOR) */
      substitution();  /** S-Box substitutions take place, result goes to sub[]
                          */
      permutation();   /**  permutates the result from S-Boxes substitution,
                          result goes from sub[] to p[]*/

      /* The drivers performs 'f' function & resultant is XORed with L(n-1) */
      xor_two(); /** Performs XOR of Ln-1 and f(R(n-1), Kn) */
      /* New Drive R(n) is ready to take the seat, currently resides in xor2[]*/

      /* For the next iteration,
       * New Drive L(n)= old Driver R(n-1)
       */
      for (i = 0; i < 32; i++)
        left[i] = right[i];
      /*
       * New Driver R(n) comes and takes seat */
      for (i = 0; i < 32; i++)
        right[i] = xor2[i];
    }

    /* concatenate the final result from 16 cycles in the formation - R16,L16 */
    for (i = 0; i < 32; i++)
      temp[i] = right[i];
    for (i = 32; i < 64; i++)
      temp[i] = left[i - 32];

    /* Applying the final permutation- inverseIP over temp[], result comes in
     * inv[]*/
    inverseIP();

    /* Converting Binary Matrix to HEX
     * Logic - consider 8 bits as two groups of 4-4 bits, then convert these 4
     * bits to HEX as
     * (3rd bit *8)+(2nd bit*4)+(1st bit*2)+(0th bit*1)
     * 8 rows i.e. one character per row
     * For each char, 2 groups of 4-4 columns and 1 bit per column.
     */
    int sss = 0;
    for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j = j + 4) {
        sss = inv[i][j] * 8 + inv[i][j + 1] * 4 + inv[i][j + 2] * 2 +
              inv[i][j + 3] * 1;
        if (sss <= 9) {
          EmsgHEX[++Emsgi] = (char)(sss + 48); // to represent 0-9 as char
        } else {
          EmsgHEX[++Emsgi] = (char)(sss + 87); // to represent a-f as char
        }
      }
    }
    /* */

    /* Converting Binary Matrix to char
      * Logic - (7th bit *128)+(6th bit *64)+(5th bit *32)+ .... +(1st
     * bit*2)+(0th bit*1)
      * 8 rows i.e. one character per row
      * For each char, 8 columns i.e. 1 bit per column
      */

    for (i = 0; i < 8; i++) {
      k = 128; // as 2^7 = 128
      d = 0;
      for (j = 0; j < 8; j++) {
        d += inv[i][j] * k;
        k = k / 2;
      }
      // Ascii to char
      final[++encryptedMsgIndex] = (char)d;
    }
  }
  final[++encryptedMsgIndex] = '\0';

  cout << "\nEncyption Key HEX  : 133457799bbcdff1";
  cout << "\nPlain  Text   HEX  : " << OmsgHEX;
  cout << "\nCipher Text   HEX  : " << EmsgHEX;

  return final;
}

/*
 * Xor the expanded right half with key (48 bits XOR)
 */
void Des::xor_oneE(int round) {
  for (int i = 0; i < 48; i++) {
    xor1[i] = expansion[i] ^ keyi[round - 1][i];
  }
}
