Stream Ciphers
==============

:section: 2
:course: Cryptography I
:url: https://www.coursera.org/course/crypto


A cipher is defined over (K, M, C) where K is set of all possbile keys, M is set of all possbile messages and C is set of all possible ciphertexts. A cipher itself is a pair of *efficient* algorithms (E, D) where E is the encryption algorithm and D is the decryption algorithm and it has to satisfy the following condition.

|E: K x M --> C, D: K x C --> M|

such that |for all m in M and k in K: D(k, E(k,m)) = m|

Encryption algorithm E is often randomized. It takes a random set of bits each time while encrypting to randomize the ciphertext. On the other hand, Decryption algorithm is often deterministic. Many different ciphertext (generated from same message) can be decrypted down to same message.


The One Time Pad
----------------

Designed by Vernam in 1917.

|M = C = {0,1}^n| The message space is same as cipher space as shown here.

The key space is also same as the message space so |K = {0,1}^n|. Key is basically random set of bits that is as long as the message to be encrypted.

For OTP, the encryption and decryption algorithms are-

|c := E(k,m) = k xor m; m: = D(k,c) = k xor c|

OTP is very fast but the keys are very long, essentially as long as the message itself so it is hard to use in practice.


Information Theoretic Security
------------------------------

For a cipher to be secure, the ciphertext should reveal no information about the plaintext. Shannon defined the meaning of perfect cipher.

Def: A cipher (E, D) over (K, M, C) has perfect secrecy if

|for all m0, m1 in M (len(m0) =len(m1)) and for all c in C|

|Pr[E(k,m0) = c] = Pr[E(k,m1) = c]| (k is uniformly sampled from K)

If the attacker gets hold of the ciphertext, then since probability of both |m0| and |m1| (actually, all the possible messages in the message space) are same so attacker has no idea what the plaintext is. With a perfect cipher even the most powerful adversary can learn nothing about the plaintext from ciphertext.

So, ciphertext only attacks are not possible but other attacks maybe.


**Lemma: OTP has perfect secrecy**

Proof:

|lemma1_1|

Now, if |lemma1_2| and since \|K\| is also constant so, RHS of the above equation becomes constant. So, LHS is also constant for all the values of m, therefore the cipher has perfect secrecy.

For OTP, only one key can map m to c. Now,

|lemma1_3|

Thus OTP has perfect secrecy and there is no CT only attack. The the keys are as long as the message which makes it practically hard to use.

But according to Shannon's lemma

|perfect secrecy => key_len >= msg_len|

practical ciphers are going to be insecure.


Stream Ciphers
--------------

OTP can be made practical by replacing "random" key by "psuedorandom" key generated using Psuedo Random Generator.

PRG (Psuedo Random Generator) is a function that maps s bit long *seed* to n bit long key given the condition that n is very very large than s.

|G: {0,1}^s --> {0,1}^n, n >> s|

The PRG should be efficiently computable by deterministic algorithm. Function has nothing random in it. The only thing random here is the seed and also the output should look random.

Stream Cipher works by taking a very small random seed, then expanding it with PRG to the size of the message, then XORing the message and expanded seed just like in OTP to get the cipher text.

|c = E(k,m) := m xor G(k); m = D(k,c) := c xor G(k)|

Since the random seed is very small than the message length, Stream Ciphers cannot have perfect secrecy. So, is it secure? To answer than, we need a different definition of security. The security will depend on the specific PRG.

**PRG must be unpredictable**

Suppose the PRG used is predictable in a way that there is some value i, such that if first i bits of the output of PRG is function is known then using some efficient algorithm, rest of the output can be known. If this is the case then stream cipher would not be secure.

|prg_unpredictable|

If an attacker intercepts the cipher text and by some prior knowledge, he knows the initial part of the message is some known value (for e.g. SMTP mail messages have a header that start with 'from:'). Then the ciphertext can be XOR'ed with message's initials to obtain initial part of the psuedorandom sequence. Then this can be fed into the above discussed algorithm to generate the entire psuedorandom sequence which can be then used to decrypt the entire message.

Even if one bit can be predicted, it can be used to find the next bit and repeat the process to get the entire plaintext. So, PRG must be completely unpredictable.

**Definition of predictability**

We say that |G: K --> {0,1}^n| is **predictable** if:

|prg_predictable|

for some non-negligible |e (e >= 1/(2^30))|

So, PRG is unpredictable if it is not predictable meaning that for all value of i, no efficient algorithm can predit bit (i+1) for non-negligible value |e|.

**Weak PRGs** - Linear Congruential Generator is one example of weak PRG. It has 3 paramters a, b and p where a and b are integers and p is a prime. Also, glibc's random() function which is another weak PRG should never be used in practice.


Negligible and Non-negligible
-----------------------------

In practice: |e| is a scalar and

- |e| non-neg:    |e >= 1/(2^30)| (2^30 = 1GB, so likely to happen over 1GB of data)
- |e| negligible: |e <= 1/(2^80)| (won't happen over life of key)

In theory of cryptography, the definition is somewhat different-

|e| is a function |e: Z^(>=0) --> R^(>=0)| and

- |e| non-neg: |exists d: e(a) >= 1/a^d| infinitely often (|e| >= 1/poly, for many |lambda|)
- |e| negligible: |for all d, a >= a_d: e(a) <= 1/a^d| (|e| <= 1/poly, for large |lambda|)

References

- http://math.stackexchange.com/questions/180236/trouble-understanding-the-theory-behind-negligible-functions-and-their-applicati
- http://cs.stackexchange.com/questions/11073/negligible-function-in-cryptography


Attacks on Stream Ciphers and OTP
---------------------------------

** Attack 1: Two Time Pad**

Never use the same stream cipher key more than once.

|c1 <-- m1 xor PRG(k); c2 <-- m2 xor PRG(k)|

Eaves dropper does |c1 xor c2 --> m1 xor m2|

There is enough redundancy in English and ASCII encoding that given the XOR of two plaintext, they can be recovered back.

|m1 xor m2 --> m1, m2|

Examples of Two Time Pad:

In **Project Vernona** during WW2, Russians constructed their keys by throwing dice and since it was laborious to generate these pads so they ended up using the same key for multiple messages. US intelligence was able to intercept the ciphertext and decrypted thousands of plaintexts.

In **MS-PPTP (windows NT)**, client and server used a private key generated using PRG and used it to encrypt the traffic they exchanged. All the communication from each side was done as a single stream so, the same key was used to encrypt both streams and this two time pad was taking place. Hence, it was possible to decrypt all the traffic. The server and the client should have used different keys.

In **802.11b WEP** when the machine and router communicated, the plaintext was added a checksum (not important) and then a stream cipher was generated with PRG. This PRG takes a seed and a value ``IV`` (Initialization Vector) as input. Since the same key should not be used twice so to add randomness to the PRG output, the value of ``IV`` is incremented for every next message. The message plus the checksum are XOR'ed with the key to generate the ciphertext. Then the value ``IV`` and the ciphertext are exchanged so that the other party can decrypt it. Size of ``IV`` is 24 bits and that of the key is 104 bits.

Length of ``IV`` is 24 bits, so it is repeated after |2^64 = 16M| frames thus two time pad occurs. So, if the eavesdropper captures first 40 million frames, then for every next frame he intercepts, he can decrypt them. Another problem is that in many 802.11 cards ``IV`` resets to 0 after power cycle, so there won't even be a need to wait for 16M frames.

Yet another problem with WEP is that the ``IV`` values used for PRG are very closely related so the generated keys are also very same. The PRG used in WEP is called RC4. There was an attack invented in 2001 on RC4 such that only after a million frames, the secret key can be recovered. Now, even better attacks have come up with which only 40,000 frames are sufficient to recover the secret key.

When a stream cipher is used for **disk encryption**, the encrypted file is vulnerable to information leak. Suppose an encrypted text file is stored on the disk and the user changes just a single word in it, re-encrypts it and saves it back. Now, if the attacker made a snapshot of the file before the edit and after, then he can compare the two and find out about exactly where the edit was made. Since the same key was used again to encrypt two partially different messages, two time pad occurs. Thus for disk encryption, do not use stream cipher.

Two Time Pad Summary

- Network traffic: negotiate new key for every session (e.g. TLS)
- Disk encryption: typically do not use a stream cipher

**Attack 2: No integrity**

One Time Pad or the stream ciphers can only provide confidentiality but not integrity. Suppose the attacker becomes active (e.g. MITM attack) and tries to modify the ciphertext by XOR'ing it with a certain value p. The party that is going to decrypt it has no knowledge that the ciphertext was tampered. When the tampered ciphertext is decrypted, the result would be the XOR of plaintext and value p. Therefore, we can see that just by affecting the ciphertext by value p, the attacker can affect the plaintext by the direct value of p.

Suppose a user sends a message that starts with string "From: Bob" encrypted with stream cipher. Lets assume that the attacker knows that plaintext starts with this string. Then he can specifically attack the 3 bytes ("Bob") so that the result is something else, say "Eve". Then he can XOR that value with the ciphertext, the receiver has no idea that ciphertext was tampered and thinks that the message is from Eve. So, even without knowing about the secret key, attacks are possible on stream ciphers.

So, modifications to ciphertext are undetected and have predictable impact on plaintext. Thus, **OTP is malleable.**



.. |E: K x M --> C, D: K x C --> M| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20E%3A%20K%20x%20M%20%5Crightarrow%20C%2C%20D%3A%20K%20x%20C%20%5Crightarrow%20M
.. |for all m in M and k in K: D(k, E(k,m)) = m| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20m%20%5Cin%20M%2C%20k%20%5Cin%20K%3A%20D%28k%2C%20E%28k%2Cm%29%29%20%3D%20m
.. |M = C = {0,1}^n| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20M%20%3D%20C%20%3D%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D
.. |K = {0,1}^n| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20K%20%3D%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D
.. |c := E(k,m) = k xor m; m: = D(k,c) = k xor c| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20c%20%3A%3D%20E%28k%2Cm%29%20%3D%20k%20%5Coplus%20m%3B%20m%3A%20%3D%20D%28k%2Cc%29%20%3D%20k%20%5Coplus%20c
.. |for all m0, m1 in M (len(m0) =len(m1)) and for all c in C| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20m_%7B0%7D%2C%20m_%7B1%7D%20%5Cin%20M%20%5C%20%28given%5C%20len%28m_%7B0%7D%29%20%3D%20len%28m_%7B1%7D%29%5C%20and%20%5C%20%5Cforall%20c%20%5Cin%20C
.. |m0| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20m_%7B0%7D
.. |m1| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20m_%7B1%7D
.. |Pr[E(k,m0) = c] = Pr[E(k,m1) = c]| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20Pr%5BE%28k%2Cm_%7B0%7D%29%20%3D%20c%5D%20%3D%20Pr%5BE%28k%2Cm_%7B0%7D%29%20%3D%20c%5D%20%5C%20where%20%5C%20k%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K
.. |lemma1_1| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20m%2C%20c%3A%20%5CPr%5Climits_%7Bk%7D%20%5BE%28k%2Cm%29%20%3D%20c%5D%20%3D%20%5Cfrac%7B%5C%23keys%5C%20k%20%5Cin%20K%3A%20E%28k%2Cm%29%20%3D%20c%7D%7B%7CK%7C%7D
.. |lemma1_2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20m%2C%20c%3A%20%5C%23%5C%7Bk%20%5Cin%20K%3A%20E%28k%2Cm%29%20%3D%20c%5C%7D%20%3D%20constant
.. |lemma1_3| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20if%5C%20E%28k%2Cm%29%20%3D%20c%20%5CRightarrow%20k%20%5Coplus%20m%20%3D%20c%20%5CRightarrow%20k%20%3D%20m%20%5Coplus%20c%20%5CRightarrow%20%5C%23%5C%7Bk%20%5Cin%20K%3A%20E%28k%2Cm%29%20%3D%20c%5C%7D%20%3D%201%5C%20%5Cforall%20m%2Cc
.. |perfect secrecy => key_len >= msg_len| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20perfect%5C%20secrecy%5C%20%5CRightarrow%20%7CK%7C%20%5Cgeq%20%7CM%7C
.. |G: {0,1}^s --> {0,1}^n, n >> s| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20G%3A%20%5C%7B0%2C1%5C%7D%5E%7Bs%7D%20%5Crightarrow%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D%5C%20given%5C%20n%20%5Cgg%20s
.. |c = E(k,m) := m xor G(k); m = D(k,c) := c xor G(k)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20c%20%3D%20E%28k%2Cm%29%20%3A%3D%20m%20%5Coplus%20G%28k%29%3B%20m%20%3D%20D%28k%2Cc%29%20%3A%3D%20c%20%5Coplus%20G%28k%29
.. |prg_unpredictable| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cexists%20i%3A%20G%28k%29%20%5Cleft%20%7C_%7B1%2C..%2Ci%7D%20%5Coverset%7Balg.%7D%7B%5Crightarrow%7D%20G%28k%29%20%5Cleft%20%7C_%7Bi&plus;1%2C..%2Cn%7D
.. |G: K --> {0,1}^n| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20G%3A%20K%20%5Crightarrow%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D
.. |prg_predictable| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cexists%5C%20eff%5C%20algo.%5C%20A%5C%20and%5C%20%5Cexists%5C%201%20%5Cleq%20i%20%5Cleq%20%28n-1%29%3A%20%5CPr%5Climits_%7Bk%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K%7D%5BA%28G%28k%29%29%7C_%7B1%2C..%2Ci%7D%20%3D%20G%28k%29%7C_%7Bi&plus;1%7D%5D%20%5Cgeq%201/2%20&plus;%20%5Cvarepsilon
.. |e (e >= 1/(2^30))| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cvarepsilon%5C%20%28say%5C%20%5Cvarepsilon%20%5Cgeq%20%5Cfrac%7B1%7D%7B2%5E%7B30%7D%7D%29
.. |e| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cvarepsilon
.. |e >= 1/(2^30)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cvarepsilon%20%5Cgeq%201/2%5E%7B30%7D
.. |e <= 1/(2^80)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cvarepsilon%20%5Cleq%201/2%5E%7B80%7D
.. |e: Z^(>=0) --> R^(>=0)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cvarepsilon%3A%20Z%5E%7B%5Cgeq%200%7D%20%5Crightarrow%20R%5E%7B%5Cgeq%200%7D
.. |exists d: e(a) >= 1/a^d| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cexists%20d%3A%20%5Cvarepsilon%20%28%5Clambda%29%20%5Cgeq%201/%5Clambda%5E%7Bd%7D
.. |lambda| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Clambda
.. |for all d, a >= a_d: e(a) <= 1/a^d| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20d%2C%20%5Clambda%20%5Cgeq%20%5Clambda_%7Bd%7D%3A%20%5Cvarepsilon%28%5Clambda%29%20%5Cleq%201/%5Clambda%5E%7Bd%7D
.. |c1 <-- m1 xor PRG(k); c2 <-- m2 xor PRG(k)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20c_%7B1%7D%20%5Cleftarrow%20m_%7B1%7D%20%5Coplus%20PRG%28k%29%3B%20c_%7B2%7D%20%5Cleftarrow%20m_%7B2%7D%20%5Coplus%20PRG%28k%29
.. |c1 xor c2 --> m1 xor m2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20c_%7B1%7D%20%5Coplus%20c_%7B2%7D%20%5Crightarrow%20m_%7B1%7D%20%5Coplus%20m_%7B2%7D
.. |m1 xor m2 --> m1, m2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20m_%7B1%7D%20%5Coplus%20m_%7B2%7D%20%5Crightarrow%20m_%7B1%7D%2C%20m_%7B2%7D
.. |2^64 = 16M| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%202%5E%7B64%7D%20%3D%2016M