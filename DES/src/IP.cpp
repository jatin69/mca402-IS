#include "./des.hpp"

/*
Initial permutation, algorithmically made.
note that: standard PC-1 goes from 1 to 64
but here to handle index we go from 0 to 63
Data stored stored to ip
*/
void Des::IP() {
  int k = 58, i;
  for (i = 0; i < 32; i++) {
    /* k-1 is done to handle 0th index, kth index of message becomes Ith index
       of IP
            Traditionally, 58th index of message becomes 1st index of IP, but we
       need to use index 0 as well,
            so here we use, 57th index of message becomes 0th index of IP*/
    ip[i] = total[k - 1];
    if (k - 8 > 0)
      k = k - 8;
    else
      k = k + 58;
  }
  k = 57;
  for (i = 32; i < 64; i++) {
    ip[i] = total[k - 1];
    if (k - 8 > 0)
      k = k - 8;
    else
      k = k + 58;
  }
}

/*
 * Final permutation, performed at the end of 16 cycles.
 * Inverse of the Initial Permutation IP
 */
void Des::inverseIP() {
  int p = 40, q = 8, k1, k2, i, j;
  // for 8 rows
  for (i = 0; i < 8; i++) {
    k1 = p;
    k2 = q;
    // for 8 columns
    for (j = 0; j < 8; j++) {
      // even column
      if (j % 2 == 0) {
        inv[i][j] = temp[k1 - 1];
        k1 = k1 + 8;
      }
      // odd column
      else {
        inv[i][j] = temp[k2 - 1];
        k2 = k2 + 8;
      }
    }
    // for subsequent rows, decrement p,q by 1
    p = p - 1;
    q = q - 1;
  }
}
