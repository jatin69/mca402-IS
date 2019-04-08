#include "./des.hpp"

/*
Handles the complete key generation process for all cycles.
*/
void Des::keygen() {
  /* PC-1 generated & applied.
      Converts 64 bit key to 56 bit key
      */
  applyPC1();

  int i, j;
  // splitting into Left (Ck) and Right (Dk) Halves of 28-28 each
  for (i = 0; i < 28; i++) {
    ck[i] = pc1[i];
  }
  int k = 0;
  for (i = 28; i < 56; i++) {
    dk[k] = pc1[i];
    k++;
  }

  int noshift = 0, round;
  for (round = 1; round <= 16; round++) {
    // no of Left shifts required at each Cycle
    if (round == 1 || round == 2 || round == 9 || round == 16)
      noshift = 1;
    else
      noshift = 2;

    // shift key by required
    while (noshift--) {
      int t;
      t = ck[0];
      for (i = 0; i < 28; i++)
        ck[i] = ck[i + 1];
      ck[27] = t;

      t = dk[0];
      for (i = 0; i < 28; i++)
        dk[i] = dk[i + 1];
      dk[27] = t;
    }

    /* applied permutation choice
            Converts 56 bit key to 48 bit key
            */
    applyPC2();

    // Hold Kn of this cycle in Keyi array, round-1 to manage index
    for (i = 0; i < 48; i++)
      keyi[round - 1][i] = z[i];
  }
}

/*
Applied PC-1 to keys
intelligently applied.
stored to pc1
*/
void Des::applyPC1() {
  int k = 57, i;
  for (i = 0; i < 28; i++) {
    pc1[i] = key[k - 1];
    if (k - 8 > 0)
      k = k - 8;
    else
      k = k + 57;
  }
  k = 63;
  for (i = 28; i < 52; i++) {
    pc1[i] = key[k - 1];
    if (k - 8 > 0)
      k = k - 8;
    else
      k = k + 55;
  }

  k = 28;
  for (i = 52; i < 56; i++) {
    pc1[i] = key[k - 1];
    k = k - 8;
  }
}

/* Applies PC-2 to Key*/
void Des::applyPC2() {
  int per[56], i, k;
  // concatenate CkDk to form 'per', then apply PC-2 to it
  for (i = 0; i < 28; i++)
    per[i] = ck[i];
  k = 0;
  for (i = 28; i < 56; i++)
    per[i] = dk[k++];

  int PC2[] = {14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
               26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
               51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
  // did -1 in PC-2 to start indexes from 0
  for (int i = 0; i < 48; ++i) {
    z[i] = per[PC2[i] - 1];
  }
}
