#include "./des.hpp"

/* key HEX is : 133457799bbcdff1 */
int key[64] = {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
               1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1,
               1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1};


int main() {
  Des d1, d2;
  string msg, msg1;

  cout << "\n ** Data Encryption Standard **\n";
  cout << "\nEnter Plaintext    : ";
  getline(cin, msg);

  msg1 = d1.Encrypt(strdup(msg.c_str()));
  cout << "\n";

  cout << "\nDecrypting message ... ";

  cout << "\nPlain Text: " << d2.Decrypt(strdup(msg1.c_str())) << "\n\n";

  // cout<<"\nPlain Text: "<<str<<endl;
  // cout<<"\nCipher Text  : \n"<<str1<<endl;
  return 0;
}
