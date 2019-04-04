#include "./aes.hpp"


unsigned char *AES::PaddingNulls(unsigned char in[], unsigned int inLen,
                                 unsigned int alignLen) {
  unsigned char *alignIn = new unsigned char[alignLen];
  memcpy(alignIn, in, inLen);
  return alignIn;
}

unsigned int AES::GetPaddingLength(unsigned int len) {
  return (len / blockBytesLen) * blockBytesLen;
}
