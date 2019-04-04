#include "./aes.hpp"

// ECB - Electronic code book method
// straightforward block by block encryption

unsigned char *AES::EncryptECB(unsigned char in[], unsigned int inLen,
                               unsigned char key[], unsigned int &outLen) {
  outLen = GetPaddingLength(inLen);
  unsigned char *alignIn = PaddingNulls(in, inLen, outLen);
  unsigned char *out = new unsigned char[outLen];
  for (unsigned int i = 0; i < outLen; i += blockBytesLen) {
    EncryptBlock(alignIn + i, out + i, key);
  }

  delete[] alignIn;

  return out;
}

unsigned char *AES::DecryptECB(unsigned char in[], unsigned int inLen,
                               unsigned char key[], unsigned int &outLen) {
  outLen = GetPaddingLength(inLen);
  unsigned char *alignIn = PaddingNulls(in, inLen, outLen);
  unsigned char *out = new unsigned char[outLen];
  for (unsigned int i = 0; i < outLen; i += blockBytesLen) {
    DecryptBlock(alignIn + i, out + i, key);
  }

  delete[] alignIn;

  return out;
}
