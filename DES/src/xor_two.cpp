#include "./des.hpp"

/* Performs XOR of Ln-1 and f(R(n-1), Kn)*/
void Des::xor_sides() {
  for (int i = 0; i < 32; i++) {
    xor2[i] = left[i] ^ p[i];
  }
}
