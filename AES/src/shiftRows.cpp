#include "./aes.hpp"

// shift row i on n positions
void AES::ShiftRow(unsigned char **state, int i, int n) 
{
  unsigned char t;
  int k, j;
  for (k = 0; k < n; k++) {
    t = state[i][0];
    for (j = 0; j < Nb - 1; j++) {
      state[i][j] = state[i][j + 1];
    }
    state[i][Nb - 1] = t;
  }
}

void AES::ShiftRows(unsigned char **state) {
  ShiftRow(state, 1, 1);
  ShiftRow(state, 2, 2);
  ShiftRow(state, 3, 3);
}

void AES::InvShiftRows(unsigned char **state) {
  ShiftRow(state, 1, Nb - 1);
  ShiftRow(state, 2, Nb - 2);
  ShiftRow(state, 3, Nb - 3);
}
