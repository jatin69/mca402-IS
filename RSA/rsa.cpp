#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int p, q, n, r, e, d;
bool isPrime(int);
bool areCoprime(int, int);
string trim(string);
string intToBinary(int);
int cipher(int, string);
void encryption();
void decryption();
int choice();
void generateKeys();

bool isPrime(int x) {
  if (x <= 1)
    return false;
  for (int i = 2; i <= sqrt(x); i++) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

bool areCoprime(int x, int y) {
  for (int i = 2; i <= sqrt(min(x, y)); i++) {
    if (x % i == 0 && y % i == 0)
      return false;
  }
  return true;
}

string trim(string s) {
  while (s.at(0) == ' ') {
    s = s.substr(1, s.length() - 1);
  }
  while (s.at(s.length() - 1) == ' ') {
    s = s.substr(0, s.length() - 1);
  }

  return s;
}

string intToBinary(int a) {
  string b = "";
  while (a != 0) {
    if (a % 2 == 1)
      b = "1" + b;
    else
      b = "0" + b;

    a /= 2;
  }
  return b;
}

int cipher(int m, string s) {
  int c = 1;
  for (int i = 0; i < s.size(); i++) {
    c = (c * c) % n;
    if (s.at(i) == '1')
      c = (c * m) % n;
  }
  return c;
}

void encryption() {
  cout << endl;
  cout << "Enter a message: ";
  string message;
  cin.ignore();
  getline(cin, message);

  cout << endl;
  cout << "Plaintext message in numeric form: ";
  for (int i = 0; i < message.size(); i++)
    cout << (int)message.at(i) << " ";

  cout << endl;
  cout << "Encrypted message in numeric form: ";
  for (int i = 0; i < message.size(); i++)
    cout << cipher((int)message.at(i), intToBinary(e)) << " ";

  cout << "\n";
}

void decryption() {
  cout << endl;
  cout << "Enter the components of the encrypted message separating each by a "
          "space: ";
  string input;
  cin.ignore();
  getline(cin, input);
  input = trim(input);

  int space;
  string number;
  vector<int> numbers;
  while (input.length() != 0) {
    space = input.find(" ");
    if (space == -1) {
      number = input;
      input = "";
    } else {
      number = input.substr(0, space);
      input = trim(input.substr(space));
    }

    numbers.push_back(stoi(number));
  }

  int asciiComponents[numbers.size()];
  for (int i = 0; i < numbers.size(); i++)
    asciiComponents[i] = cipher(numbers.at(i), intToBinary(d));

  cout << endl;
  cout << "Decrypted message in numeric form: ";
  for (int i = 0; i < numbers.size(); i++)
    cout << asciiComponents[i] << " ";

  cout << endl;
  cout << "Decrypted message in text form: ";
  for (int i = 0; i < numbers.size(); i++)
    cout << (char)asciiComponents[i];

  cout << "\n";
}

int choice() {
  cout << endl;
  cout << "Public Key: (" << e << ", " << n << ")" << endl;
  cout << "Private Key: (" << d << ", " << n << ")" << endl;
  cout << "Generate Keys (0), Encryption (1), Decryption (2), or EXIT "
          "(anything else)? ";
  string decision;
  cin >> decision;
  if (decision == "0")
    return 0;
  else if (decision == "1")
    return 1;
  else if (decision == "2")
    return 2;
  else
    return 3;
}

void generateKeys() {
  cout << endl;
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

  int trial = 1;
  while ((trial * r + 1) % d != 0)
    trial++;
  e = (trial * r + 1) / d;
  cout << "Choose a non-negative integer k to set public key = " << e << " + "
       << r << "k: ";

  int k;
  cin >> k;
  while (k < 0) {
    cout << "Invalid. Try again: ";
    cin >> k;
  }
  e = e + (r * k);
}

int main() {
  cout << "RSA Cryptosystem C++ Program" << endl;
  cout << "----------------------------" << endl;
  generateKeys();

  int choose;
  while (true) {
    choose = choice();
    if (choose == 0)
      generateKeys();
    else if (choose == 1)
      encryption();
    else if (choose == 2)
      decryption();
    else
      break;
  }

  return 0;
}
