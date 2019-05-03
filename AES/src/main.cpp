#include <iostream>
#include "./aes.hpp"
#include <cassert>
#include <cstring>

using namespace std;

struct HexCharStruct{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs){
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c){
    return HexCharStruct(_c);
}

void hexD(unsigned char* c){
  int n = strlen((char*)c);
  for(int i=0; i<n; ++i){
    cout << hex(c[i]) ; 
  }
}

void runAllTests();
void runCustomTest(string plainTextString, string keyString);

int main(){
  // use this to run all tests
  // runTests();

  cout << "********** AES **************\n\n";
  cout << "Default Test : \n\n";
  string plainText = "Thisisagoodday.";
  string key = "gjvhcbkjwerfgvervelcnwjcnekljcv";
  runCustomTest(plainText, key);

  cout << "\n\nCustom Test : \n\n";
  cout << "Enter Plaintext          : " ;
  getline(cin, plainText);
  cout << "Enter Key                : " ;
  getline(cin, key);
  cout << "\n";
  runCustomTest(plainText, key);
  
  cout << "Press Enter to exit ... ";
  cin.ignore();
  return 0;
}

void runCustomTest(string plainTextString, string keyString) {
  
  unsigned char plainText[200000];
  strcpy ((char*) plainText, plainTextString.c_str());

  unsigned char key[200000];
  strcpy ((char*) key, keyString.c_str());
  
  using std::cout;
  AES aes(256);
  cout << "Plain text               : " << plainText << "\n";
  cout << "Plain text [HEX]         : " ; hexD(plainText); cout << "\n\n";
  
  cout << "Encryption Key           : " << key << "\n";
  cout << "Encryption Key [HEX]     : "; hexD(key); cout << "\n\n";
  

  unsigned int len = 0;
  unsigned char *cipherText = aes.EncryptECB(plainText, 16 * sizeof(unsigned char), key, len);
  cout << "Cipher text is           : " << cipherText << "\n";
  cout << "Cipher text is [HEX]     : " ; hexD(cipherText); cout << "\n\n";

  unsigned char *decryptedText = aes.DecryptECB(cipherText, 16 * sizeof(unsigned char), key, len);
  cout << "Decrypted text is        : " << decryptedText << "\n";
  cout << "Decrypted text is  [HEX] : " ; hexD(decryptedText); cout << "\n\n";
  
  if(memcmp(decryptedText, plainText, 16 * sizeof(unsigned char)) == 0){
    cout << "Plaintext == Decrypted Text \n";
    cout << "AES Test Successful.\n" << endl;
  }
  
  delete[] cipherText;
  delete[] decryptedText;
}