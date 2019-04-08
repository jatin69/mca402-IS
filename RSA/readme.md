# RSA

You may use the given [prime list](./primes.txt) for assistance.

Example with small primes.

```

************** RSA Cryptosystem ************** 

Key Generations for RSA - 

Enter a prime number: 1301
Enter a different prime number: 2111

Modulus = 2746411
Totient = 2743000

Choose a random integer that is coprime with the totient: 281

Choose a non-negative integer k to set public key = 2001121 + 2743000k: 97


Public Key: (268072121, 2746411)
Private Key: (281, 2746411)

Menu : 
0. Generate Keys
1. Encryption
2. Decryption
3. exit

Choose a option : 1

Enter a message: testing with small prime numbers 

Plaintext message in numeric form: 116 101 115 116 105 110 103 32 119 105 116 104 32 115 109 97 108 108 32 112 114 105 109 101 32 110 117 109 98 101 114 115 
Encrypted message in numeric form: 602947 1160632 2035089 602947 1702560 1344367 2579339 2501935 2548246 1702560 602947 2015419 2501935 2035089 1061828 2688886 1264927 1264927 2501935 49067 1747690 1702560 1061828 1160632 2501935 1344367 491827 1061828 485223 1160632 1747690 2035089 


Public Key: (268072121, 2746411)
Private Key: (281, 2746411)

Menu : 
0. Generate Keys
1. Encryption
2. Decryption
3. exit

Choose a option : 2

Enter the components of the encrypted message separating each by a space: 602947 1160632 2035089 602947 1702560 1344367 2579339 2501935 2548246 1702560 602947 2015419 2501935 2035089 1061828 2688886 1264927 1264927 2501935 49067 1747690 1702560 1061828 1160632 2501935 1344367 491827 1061828 485223 1160632 1747690 2035089 

Decrypted message in numeric form: 116 101 115 116 105 110 103 32 119 105 116 104 32 115 109 97 108 108 32 112 114 105 109 101 32 110 117 109 98 101 114 115 
Decrypted message in text form: testing with small prime numbers


Public Key: (268072121, 2746411)
Private Key: (281, 2746411)

Menu : 
0. Generate Keys
1. Encryption
2. Decryption
3. exit

Choose a option : 3
Exiting ...

```

Example with large primes

```

************** RSA Cryptosystem ************** 

Key Generations for RSA - 

Enter a prime number: 27749
Enter a different prime number: 28319

Modulus = 785823931
Totient = 785767864

Choose a random integer that is coprime with the totient: 30011

Choose a non-negative integer k to set public key = 409104091 + 785767864k: 32971


Public Key: (25907961348035, 785823931)
Private Key: (30011, 785823931)

Menu : 
0. Generate Keys
1. Encryption
2. Decryption
3. exit

Choose a option : 1

Enter a message: my rsa works cool

Plaintext message in numeric form: 109 121 32 114 115 97 32 119 111 114 107 115 32 99 111 111 108 
Encrypted message in numeric form: 29694247 763107448 212313837 50805628 60485803 171310089 212313837 574327773 58857877 50805628 342306604 60485803 212313837 349335088 58857877 58857877 108650307 


Public Key: (25907961348035, 785823931)
Private Key: (30011, 785823931)

Menu : 
0. Generate Keys
1. Encryption
2. Decryption
3. exit

Choose a option : 2

Enter the components of the encrypted message separating each by a space: 29694247 763107448 212313837 50805628 60485803 171310089 212313837 574327773 58857877 50805628 342306604 60485803 212313837 349335088 58857877 58857877 108650307 

Decrypted message in numeric form: 109 121 32 114 115 97 32 119 111 114 107 115 32 99 111 111 108 
Decrypted message in text form: my rsa works cool


Public Key: (25907961348035, 785823931)
Private Key: (30011, 785823931)

Menu : 
0. Generate Keys
1. Encryption
2. Decryption
3. exit

Choose a option : 3
Exiting ...

```