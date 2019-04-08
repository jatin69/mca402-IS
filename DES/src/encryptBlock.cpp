#include "./des.hpp"

void Des::encryptBlock() {

    int i, round;
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
      expandMsg();     /** Convert 32-bit message to 48 bit message using E-bit
                          Selection table  */
      xor_one_encryption(round); /** Xor the expanded right half with key (48 bits XOR) */
      substitution();  /** S-Box substitutions take place, result goes to sub[]
                          */
      permutation();   /**  permutates the result from S-Boxes substitution,
                          result goes from sub[] to p[]*/

      /* The drivers performs 'f' function & resultant is XORed with L(n-1) */
      xor_sides(); /** Performs XOR of Ln-1 and f(R(n-1), Kn) */
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

    /* concatenate the finalStr result from 16 cycles in the formation - R16,L16 */
    for (i = 0; i < 32; i++)
      temp[i] = right[i];
    for (i = 32; i < 64; i++)
      temp[i] = left[i - 32];

    /* Applying the finalStr permutation- inverseIP over temp[], result comes in
     * inv[]*/
    inverseIP();

}

/*
 * Xor the expanded right half with key (48 bits XOR)
 */
void Des::xor_one_encryption(int round) {
  for (int i = 0; i < 48; i++) {
    xor1[i] = expansion[i] ^ keyi[round - 1][i];
  }
}
