#include "./aes.hpp"

// CBC - cipher block chaining

unsigned char *AES::EncryptCBC(unsigned char in[], unsigned int inLen,
                               unsigned char key[], unsigned char *iv,
                               unsigned int &outLen) {
  outLen = GetPaddingLength(inLen);
  unsigned char *alignIn = PaddingNulls(in, inLen, outLen);
  unsigned char *out = new unsigned char[outLen];
  unsigned char *block = new unsigned char[blockBytesLen];
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < outLen; i += blockBytesLen) {
    XorBlocks(block, alignIn + i, block, blockBytesLen);
    EncryptBlock(block, out + i, key);
  }

  delete[] block;
  delete[] alignIn;

  return out;
}

unsigned char *AES::DecryptCBC(unsigned char in[], unsigned int inLen,
                               unsigned char key[], unsigned char *iv,
                               unsigned int &outLen) {
  outLen = GetPaddingLength(inLen);
  unsigned char *alignIn = PaddingNulls(in, inLen, outLen);
  unsigned char *out = new unsigned char[outLen];
  unsigned char *block = new unsigned char[blockBytesLen];
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < outLen; i += blockBytesLen) {
    DecryptBlock(alignIn + i, out + i, key);
    XorBlocks(block, out + i, out + i, blockBytesLen);
  }

  delete[] block;
  delete[] alignIn;

  return out;
}
