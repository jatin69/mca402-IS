
#include "./rsa.hpp"


ulli cipher(ulli m, string s) {
  ulli c = 1;
  for (ulli i = 0; i < s.size(); i++) {
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
  for (ulli i = 0; i < message.size(); i++)
    cout << (ulli)message.at(i) << " ";

  cout << endl;
  cout << "Encrypted message in numeric form: ";
  for (ulli i = 0; i < message.size(); i++)
    cout << cipher((ulli)message.at(i), intToBinary(e)) << " ";

  cout << "\n";
}

void decryption() {
  cout << endl;
  cout << "Enter the components of the encrypted message separating each by a "
          "space: ";
  string input;
  cin.ignore();
  getline(cin, input);
  input = trimSpace(input);

  ulli space;
  string number;
  vector<ulli> numbers;
  while (input.length() != 0) {
    space = input.find(" ");
    if (space == -1) {
      number = input;
      input = "";
    } else {
      number = input.substr(0, space);
      input = trimSpace(input.substr(space));
    }

    numbers.push_back(stoull(number));
  }

  ulli asciiComponents[numbers.size()];
  for (ulli i = 0; i < numbers.size(); i++)
    asciiComponents[i] = cipher(numbers.at(i), intToBinary(d));

  cout << endl;
  cout << "Decrypted message in numeric form: ";
  for (ulli i = 0; i < numbers.size(); i++)
    cout << asciiComponents[i] << " ";

  cout << endl;
  cout << "Decrypted message in text form: ";
  for (ulli i = 0; i < numbers.size(); i++)
    cout << (char)asciiComponents[i];

  cout << "\n";
}

