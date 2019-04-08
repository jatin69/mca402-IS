#include "./rsa.hpp"

void generateKeys() {
  cout << "\nKey Generations for RSA - \n\n";
  cout << "Enter a prime number: ";
  cin >> p;
  while (!isPrime(p)) {
    cout << "Invalid. Try again: ";
    cin >> p;
  }

  cout << "Enter a different prime number: ";
  cin >> q;
  while (!isPrime(q) || q == p) {
    cout << "Invalid. Try again: ";
    cin >> q;
  }

  n = p * q;
  if (n < 127) {
    cerr << "ERROR: Modulus is less than 127. Program Terminated.";
    exit(1);
  }

  cout << endl;

  cout << "Modulus = " << n << endl;
  r = (p - 1) * (q - 1);
  cout << "Totient = " << r << endl;
  cout << endl;
  cout << "Choose a random integer that is coprime with the totient: ";
  cin >> d;
  while (d <= 1 || !areCoprime(d, r)) {
    cout << "Invalid. Try again: ";
    cin >> d;
  }

  cout << endl;

  ulli trial = 1;
  while ((trial * r + 1) % d != 0)
    trial++;
  e = (trial * r + 1) / d;
  cout << "Choose a non-negative integer k to set public key = " << e << " + "
       << r << "k: ";

  ulli k;
  cin >> k;
  while (k < 0) {
    cout << "Invalid. Try again: ";
    cin >> k;
  }
  e = e + (r * k);
}
