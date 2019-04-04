#include "./aes.hpp"

// CFB - cipher feedback mode

unsigned char *AES::EncryptCFB(unsigned char in[], unsigned int inLen,
                               unsigned char key[], unsigned char *iv,
                               unsigned int &outLen) {
  outLen = GetPaddingLength(inLen);
  unsigned char *alignIn = PaddingNulls(in, inLen, outLen);
  unsigned char *out = new unsigned char[outLen];
  unsigned char *block = new unsigned char[blockBytesLen];
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < outLen; i += blockBytesLen) {
    EncryptBlock(block, out + i, key);
    XorBlocks(alignIn + i, block, out + i, blockBytesLen);
    memcpy(block, out + i, blockBytesLen);
  }

  delete[] block;
  delete[] alignIn;

  return out;
}

unsigned char *AES::DecryptCFB(unsigned char in[], unsigned int inLen,
                               unsigned char key[], unsigned char *iv,
                               unsigned int &outLen) {
  outLen = GetPaddingLength(inLen);
  unsigned char *alignIn = PaddingNulls(in, inLen, outLen);
  unsigned char *out = new unsigned char[outLen];
  unsigned char *block = new unsigned char[blockBytesLen];
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < outLen; i += blockBytesLen) {
    DecryptBlock(block, out + i, key);
    XorBlocks(alignIn + i, block, out + i, blockBytesLen);
    memcpy(block, alignIn + i, blockBytesLen);
  }

  delete[] block;
  delete[] alignIn;

  return out;
}
