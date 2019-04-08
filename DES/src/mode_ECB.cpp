#include "./des.hpp"

char* Des::mode_ECB_encrypt(char * Text1) {
  
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

  /* 
   * Encryption condition: message length should be multiple of eight(64 bits
   * encypted at once),
   * if not multiple of eight, 0 is appended to make it multiple of 8.
   * for eg -
   * let message length is 15. It can be divided into 2 message blocks (8+7), DES
   * needs to be run 2 times.
   * In second block 0 needs to be appended in the HEXA code of plaintext to make
   * it multiple of 8.
   */
  int messageBlocks = ceil(strlen(Text) / 8.0);

  /*
  * A DES run has 16 cycles. In a complete run it can encrypt 64 bits (8
  * characters of 8 bit each)
  * The entire message is broken into groups of 8 characters,
  * then DES is RUN on those 8 characters.
  */
  int encryptedMsgIndex = -1; // acts as index for finalStr   encrypted message
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

    encryptBlock();

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
      finalStr[++encryptedMsgIndex] = (char)d;
    }
  }
  finalStr[++encryptedMsgIndex] = '\0';

  cout << "\nEncyption Key HEX  : 133457799bbcdff1";
  cout << "\nPlain  Text   HEX  : " << OmsgHEX;
  cout << "\nCipher Text   HEX  : " << EmsgHEX;

  return finalStr;
}

char *Des::mode_ECB_decrypt(char *Text1) {

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

    decryptBlock();


    for (i = 0; i < 8; i++) {
      k = 128;
      d = 0;
      for (j = 0; j < 8; j++) {
        d = d + inv[i][j] * k;
        k = k / 2;
      }
      finalStr[mc++] = (char)d;
    }
  }
  finalStr[mc] = '\0';

  char *final1 = new char[1000];
  for (i = 0, j = strlen(Text); i < strlen(Text); i++, j++)
    final1[i] = finalStr[j];
  final1[i] = '\0';
  return (finalStr);

}