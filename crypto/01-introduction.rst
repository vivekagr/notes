Introduction to Cryptography
============================

:section: 1
:course: Cryptography I
:url: https://www.coursera.org/course/crypto


Cryptography is everywhere. Its used for web traffic encryption (HTTPS), wireless (WPA2, GSM, Bluetooth), files on disk (EFS, TrueCrypt), content protection on DVD/Bue-ray (CSS, AACS), user authentication, etc.

In Cryptography, both confidentiality and integrity have to be preserved. So, no eavesdropping and no tampering.

Symmetric Encryption is the building block of data encryption. It is called symmetric because both the encryption and the decryption function use the same key. Encryption algorithm is (and should be) publicly known. Never use a proprietary cipher. Encryption algorithms in the public domain are tested by thousands of security experts and are much more safer to use than proprietary ones which are tested and designed by only a handful of people.

``E(k, m) ==> c`` and ``D(k, c) ==> m``

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

So, ``{0,1}^2 = {00, 01, 10, 11}``.

Probability distribution ``P`` over ``U`` is a function ``P: U --> [0,1]`` (probability of every element in the set is between 0 and 1). The requirement for this to be true is that sum of all the probabilities be equal to 1.

**Examples of Probability Distribution**

Under **uniform distribution**, every element in the universe is assigned exactly the sam weight.

``for all x in U: P(x) = 1/|U|`` (``|U|`` means the size of universe/total num of elements)

**Point distribution** at ``x[0]: P(x[0]) = 1, for all x!=x[0]: P(x) = 0``. Here, all the weight is assigned to ``x[0]`` and none to the remaining elements.

.. |U = {0,1}^n| image:: http://latex.codecogs.com/gif.latex?U%20%3D%20%5C%7B0%2C1%5C%7D%5En
.. |{0,1}^n| image:: http://latex.codecogs.com/gif.latex?%5C%7B0%2C1%5C%7D%5En
.. |2^n| image:: http://latex.codecogs.com/gif.latex?2%5En
