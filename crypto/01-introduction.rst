Introduction to Cryptography
============================

:section: 1
:course: Cryptography I
:url: https://www.coursera.org/course/crypto


Cryptography is everywhere. Its used for web traffic encryption (HTTPS), wireless (WPA2, GSM, Bluetooth), files on disk (EFS, TrueCrypt), content protection on DVD/Bue-ray (CSS, AACS), user authentication, etc.

In Cryptography, both confidentiality and integrity have to be preserved. So, no eavesdropping and no tampering.

Symmetric Encryption is the building block of data encryption. It is called symmetric because both the encryption and the decryption function use the same key. Encryption algorithm is (and should be) publicly known. Never use a proprietary cipher. Encryption algorithms in the public domain are tested by thousands of security experts and are much more safer to use than proprietary ones which are tested and designed by only a handful of people.

|E(k, m) ==> c| and |D(k, c) ==> m|

where E and D are Encryption and Decryption functions, m is plain text, c is cipher-text and k is the secret key. In symmetric encryption, secret key is known only by the sending and the receiving parties.

The secret key can be used to either encrypt just one message and then change the key or it can be used to encrypt multiple messages.

Cryptography is-

- A tremendous tool
- The basis of many security mechanisms

Cryptography is not-

- The solution to all security problems
- Reliable unless implemented and used properly
- Something you should try to invent yourself

The two parts of core cryptography - secret key establishment and secure communication.

Application of cryptography-

- Digital signatures
- Anonymous communication
- Anonymous digital cash
- Elections
- Private auction


**Secure Multi-Party computation**

Suppose we are implementing the online voting system, we could have a trusted authority to whom each voter sends his encrypted votes and the authority keeps everything but the winning party's name secret. But what if the trusted authority is not longer trust-able? In cryptography, there is a theorem that says that anything that can be done with trusted authority can also be done without.

So, a protocol can be implemented such that every voter talks to one another anonymously and at the end of the protocol, desired results are outputted.

**Zero Knowledge** (proof of knowledge)

Suppose Alice knows ``N=p*q``, where p and q are fairly large numbers so that getting ``p`` and ``q`` factors from knowing just about ``N`` is very difficult. Now, if Alice wants to prove to Bob that she knows the factors without letting Bob know about any of the details, she can do it with zero knowledge proof.


Three steps in Cryptography

- Precisely specify threat model
- Propose a construction
- Prove that breaking construction under threat model will solve an underlying hard problem


Examples of Symmetric ciphers
-----------------------------

**Substitution Cipher** - An alternate character mapping table is created which contains the alternate mappings for every character in the language. When the encryption is done, every character is replaced by its alternate version from the table and the reverse process is followed for decryption.

A popular example of substitution cipher is Caesar Cipher. In Ceaser Cipher, no key is used and the substitution is fixed, namely every character is shifted by say 3, so a becomes d, b becomes e and so on. This is very easy to break.

Breaking Substitution cipher-

- Use frequency of English letters - using this, keys for some of the most common letters can be known
- Use the frequency of pair of letters (digrams) - using this, rest of the key table can be found out

This is the worst sort of encryption algorithm since given only the cipher text, attacker can get the plaintext.

**Vigener Cipher** - A key is selected, say `CRYPTO`, then the key is repeated to cover the entire length of the message to get the final key. Now the each corresponding letter from both the final key and the message are added (and modulo 26'ed) to form the ciphertext.

Message can be broken easily if the key size is known (and even if the key size is unknown, it can be determined). The ciphertext is broken into blocks of the size of key. Then we know that every first letter of each block was substituted by the same key letter and so on for every letter in the blocks, these blocks are transposed to form new set of blocks in which first block contains first letters from every previous block, second block contains second letters from every previous block and so on. Each of these new blocks are solved individually as substitution cipher and then transposed back to form the plaintext.

**Rotor Machines** - (The Herbern Machine) It's yet another form of substitution cipher. Rotor Machine is a type writer which contains the substitution table hardcoded in it in a rotor and every time a letter was pressed on the machine, the rotor rotated by one character. Again, this cipher was also broken using frequency tables.

Another rotor machine is The Enigma which is much more complex version of it containing multiple rotors and the key was initial setting of the rotors. It was used during WW2. But it was broken was well by British cryptographers.

**Data Encryption Standard** - In 1974, a group at IBM set together a cipher that was adopted to be used as a standard cipher by the government and was called Data Encryption Standard. Key space for DES is 2^56 and block size is 64 bits which was good enough in 1974. These days, it can very easily be broken using bruteforce attacks.

Today, there are more advanced ciphers such as AES (2001), Salsa20 (2008) and others.


Discrete Probability
--------------------

Reference - https://en.wikibooks.org/wiki/High_School_Mathematics_Extensions/Discrete_Probability

Advanced modern cryptography was developed as a rigorous science where constructions are always accompanied by a proof. The language used to describe the proofs relies on Discrete Probability.

Discrete probability is always defined over a universe which is denoted by ``U``. This universe in our case is always going to be a finite set, very commonly |U = {0,1}^n| a set of all n bit strings which here is denoted by |{0,1}^n|. The number of elements in this set is always |2^n|.

So, |{0,1}^2 = {00, 01, 10, 11}|.

Probability distribution P over U is a function |P: U --> [0,1]| (probability of every element in the set is between 0 and 1). The requirement for this to be true is that sum of all the probabilities be equal to 1.

**Examples of Probability Distribution**

Under **uniform distribution**, every element in the universe is assigned exactly the sam weight.

for all |x in U: P(x) = 1/|U|| (``|U|`` means the size of universe/total num of elements)

**Point distribution** at |x[0]: P(x[0]) = 1, for all x!=x[0]: P(x) = 0|. Here, all the weight is assigned to |x[0]| and none to the remaining elements.


**Events**

|A subset of U: Pr[A] = sum of all P(x) where x belongs to A is [0,1] (between 0 and 1)|

Note that |Pr[U]=1|. The set A here is called event.


**Union Bound** - For events |A1| and |A2|

|Pr[A1 U A2] <= Pr[A1] + Pr[A2]|

And if |Pr[A1 intersection A2] = null then Pr[A1 union A2] = Pr[A1] + Pr[A2]|


**Random Variable**

A random variable ``X`` is a function |X:U --> V| (from the universe into some set ``V``). Set ``V`` is where the random variable takes its value.

Example: |X: {0,1}^n --> {0,1}; X(y) = lsb(y) in {0,1}|

Suppose we have a random variable ``X``, which maps the universe |{0,1}^n| into the set |{0,1}|. So, the value of ``X`` is either 0 or 1. Given a particular ``n`` bit string sample ``y`` in the universe, random variable will just output the lsb (least significant bit) ``y``.

For the uniform distribution on ``U``: |Pr[X=0] = 1/2 ; Pr[X=1] = 1/2|

**Uniform Random Variable**

Let U be some set, e.g. |U = {0,1}^n| then

|r <--R-- U| denotes a uniform random variable ``r`` over ``U`` for all |a in U such that Pr[r = a] = 1/sizeof(U)|

Formally, r is the identity function: |r(x)=x for all x in U|


**Deterministic Algorithm** - For a particular input ``m``, always the same output ``y`` is generated.

|y <--  A(m)|

**Randomized Algorithm** - It takes input ``m`` and has implicit argument ``r``, where ``r`` is sampled anewed every time the function is run. ``n`` is sampled randomly from set of ``n`` bit strings.

|y <-- A(m; r) where r <--R-- {0,1}^n|


.. |E(k, m) ==> c| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20E%28k%2C%20m%29%20%5Crightarrow%20c
.. |D(k, c) ==> m| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20D%28k%2C%20c%29%20%5Crightarrow%20m
.. |U = {0,1}^n| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20U%20%3D%20%5C%7B0%2C1%5C%7D%5En
.. |{0,1}^n| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D%5En
.. |2^n| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%202%5En
.. |{0,1}^2 = {00, 01, 10, 11}| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D%5E2%20%3D%20%5C%7B00%2C%2001%2C%2010%2C%2011%5C%7D
.. |P: U --> [0,1]| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20P%3A%20U%20%5Crightarrow%20%5B0%2C1%5D
.. |x in U: P(x) = 1/|U|| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20x%20%5Cin%20U%3A%20P%28x%29%20%3D%201/%7CU%7C
.. |x[0]: P(x[0]) = 1, for all x!=x[0]: P(x) = 0| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20x_%7B0%7D%3A%20P%28x_%7B0%7D%29%20%3D%201%2C%20%5Cforall%20x%5Cneq%20x_%7B0%7D%3A%20P%28x%29%20%3D%200
.. |x[0]| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20x_%7B0%7D
.. |A subset of U: Pr[A] = sum of all P(x) where x belongs to A is [0,1] (between 0 and 1)| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20A%20%5Csubseteq%20U%3A%20Pr%5BA%5D%20%3D%20%5Csum%20_%7Bx%20%5Cin%20A%7D%20P%28x%29%20%5Cin%20%5B0%2C1%5D
.. |Pr[U]=1| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20Pr%5BU%5D%3D1
.. |A1| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20A_%7B1%7D
.. |A2| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20A_%7B2%7D
.. |Pr[A1 U A2] <= Pr[A1] + Pr[A2]| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20Pr%5BA_%7B1%7D%20%5Ccup%20A_%7B2%7D%5D%20%5Cleq%20Pr%5BA_%7B1%7D%5D%20+%20Pr%5BA_%7B2%7D%5D
.. |Pr[A1 intersection A2] = null then Pr[A1 union A2] = Pr[A1] + Pr[A2]| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20A_%7B1%7D%20%5Ccap%20A_%7B2%7D%20%3D%20%5Cphi%20%5CRightarrow%20Pr%5BA_%7B1%7D%20%5Ccup%20A_%7B2%7D%5D%20%3D%20Pr%5BA_%7B1%7D%5D%20+%20Pr%5BA_%7B2%7D%5D
.. |X:U --> V| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20X%3AU%20%5Crightarrow%20V
.. |X: {0,1}^n --> {0,1}; X(y) = lsb(y) in {0,1}| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20X%3A%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D%20%5Crightarrow%20%5C%7B0%2C1%5C%7D%3B%20X%28y%29%20%3D%20lsb%28y%29%20%5Cin%20%5C%7B0%2C1%5C%7D
.. |{0,1}^n| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D
.. |{0,1}| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D
.. |Pr[X=0] = 1/2 ; Pr[X=1] = 1/2| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20Pr%5BX%3D0%5D%20%3D%201/2%20%3B%20Pr%5BX%3D1%5D%20%3D%201/2
.. |U = {0,1}^n| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20U%20%3D%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D
.. |r <--R-- U| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20r%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20U
.. |a in U such that Pr[r = a] = 1/sizeof(U)| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20a%20%5Cin%20U%3A%20Pr%5Br%20%3D%20a%5D%20%3D%201/%7CU%7C
.. |r(x)=x for all x in U| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20r%28x%29%3Dx%5C%20for%5C%20x%20%5Cin%20U
.. |y <--  A(m)| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20y%20%5Cleftarrow%20A%28m%29
.. |y <-- A(m; r) where r <--R-- {0,1}^n| image:: http://latex.codecogs.com/gif.latex?%5Cfn_cm%20%5Csmall%20y%20%5Cleftarrow%20A%28m%3B%20r%29%20%5C%20where%20%5C%20r%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D
