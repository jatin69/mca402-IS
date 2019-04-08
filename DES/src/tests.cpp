#include "./des.hpp"

int test_ECB() {
  Des d1, d2;
  string msg, msg1;

  cout << "\n ** Data Encryption Standard **\n";
  cout << "\nEnter Plaintext    : ";
  getline(cin, msg);

  msg1 = d1.mode_ECB_encrypt(strdup(msg.c_str()));
  cout << "\n";

  cout << "\nDecrypting message ... ";

  cout << "\nPlain Text: " << d2.mode_ECB_decrypt(strdup(msg1.c_str())) << "\n\n";

  // cout<<"\nPlain Text: "<<str<<endl;
  // cout<<"\nCipher Text  : \n"<<str1<<endl;
  return 0;
}
