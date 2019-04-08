#include "./rsa.hpp"

ulli p = 0, q = 0, n = 0, r = 0, e = 0, d = 0;

int main() {
  cout << "\n************** RSA Cryptosystem ************** \n";
  generateKeys();

  ulli choose;
  while (true) {
    cout << "\n\n";
    cout << "Public Key: (" << e << ", " << n << ")" << endl;
    cout << "Private Key: (" << d << ", " << n << ")" << endl;
    cout << "\nMenu : \n";
    cout << "0. Generate Keys\n";
    cout << "1. Encryption\n";
    cout << "2. Decryption\n";
    cout << "3. exit\n";

    cout << "\nChoose a option : ";
    char choice;
    cin >> choice;

    switch (choice) {
    case '0':
      generateKeys();
      break;
    case '1':
      encryption();
      break;
    case '2':
      decryption();
      break;
    default:
      cout << "Exiting ...\n";
      exit(0);
    }
  }

  return 0;
}
