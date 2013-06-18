Stream Ciphers
==============

:section: 2
:course: Cryptography I
:url: https://www.coursera.org/course/crypto
:slides: http://bit.ly/128TeFB


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

**Attack 1: Two Time Pad**

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


Real World Stream Ciphers
-------------------------

**RC4 (1987) used in WEP, HTTPS**

RC4 takes variable size seed, for e.g. 128 bits and expands it into 2048 bits which is used as internal state for the generator. Then a very simple loop is executed where every iteration outputs 1 byte of output. So, the generator can be run for as long as wanted. Used in WEP and HTTPS.

Weaknesses:

- Bias in initial output Pr[2nd byte = 0] = 2/256 whereas it should be 1/256. Infact the first 256 bits are biased in this way so it is recommended to strip off the first 256 bits of generated values.
- When a long output of RC4 is takes, the sequence of ``00`` is more likely to occur. Prob(0,0) should be |1/256^2| but it is |1/256^2 + 1/256^3|. This bias kicks in after several gigabytes of generated data but nevertheless, it can still be used to predict the generator.
- Related key attacks - Like in WEP, the closesly related Initialization Vector can make it possible to recover the secret key.

So, RC4 is not recommended to use in new systems.


**CSS used in CDs/DVDs**

CSS stands for Content Scrambling System. It turned out to be a badly broken stream cipher. It is implemented in hardware due to ease and is based on a system called Linear Feedback Shift Register (LFSR).

LFSR is based on register with multiple cells where each cell contains a bit. Then the bits from certain position (called taps) are taken and XORed. Every cycle the values are right shitfted to drop the LSB and the MSB is assigned the value acquired from the previous XOR calculation. This takes very few transistors and is easy to implement in the hardware. So the seed is the initial state of LFSR.

LFSRs are used for

- DVD encryption (CSS): 2 LFSRs
- GSM encryption (A5/1,2): 3 LFSRs
- Bluetooth (E0): 4 LFSRs

**Breaking CSS**

CSS's weakness is primarily due to the regulations placed on the export of cryptographic systems from the United States. At the time that CSS was introduced, it was forbidden in the United States for manufacturers to export cryptographic systems employing keys in excess of 40 bits, a key length that had already been shown to be wholly inadequate in the face of increasing computer processing power.

How CSS works - The size of seed is 5 bytes or 40 bits. 2 LFSRs of size 17-bit and 25-bit are used. First 17-bit LFSR contains ``1`` concatnated with 2 bytes from the key and second 25-bit LFSR contains ``1`` concatnated with rest 3 bytes from the key. Both of these LFSR's give 1 byte output each. Then addition and mod 256 (also carry from previous block is added) is performed to give final 1 byte output per cycle.

Breaking - CSS can be broken in just |2^17| iterations. The first few bytes, say 20 bytes plaintext of the encrypted video file is known. This 20 byte plaintext is XORed with the corresponding encrypted content to get the 20 byte of the key (lets say K). Now, for each possible value of first 17-bit register, 20 bytes are generated. Each of those 20 bytes value are subtracted from K to get the possible 20 byte output (lets say X) of the second register. It is easy to say whether X can be a output of 2nd 25-bit LFSR or not. During the iteration, when we hit the value X which can be an output of 2nd LFSR, then we get the correct pair of values of LFSR which can be then used to predict the rest of the key and decrypt the whole movie.


**Modern Stream Ciphers - eStream**

eSTREAM is a project to "identify new stream ciphers suitable for widespread adoption", organised by the EU ECRYPT network. It was set up as a result of the failure of all six stream ciphers submitted to the NESSIE project. The call for primitives was first issued in November 2004. The project was completed in April 2008.

The PRGs from eStream project use the seed and in addition to that a nonce. Nonce is a non-repeating value for a given key. It never repeats as long as the key is fixed.

PRG: |{0,1}^s x R --> {0,1}^n|

|E(k, m; r) = m xor PRG(k ;r)|

The pair (k,r) is never used more than once. So, the key can be used many times since differing nonce makes the pair unique.

One of the ciphers that came from eStream project is **Salsa20**. It can used for both hardware and software implementations.

Salsa20: |{0,1}^(128 or 256) x {0,1}^64 --> {0,1}^n  (max n = 2^73 bits)|

It takes 128-bit or 256-bit key and 64-bit nonce.

Salsa20 (k; r) := H(k, (r, 0)) || H(k, (r, 1)) || ...

The function H takes key, nonce and serial number to generate 64 bytes output.

How function H works: (k - 16 bytes, r - 8 bytes, i - 8 bytes) is of size 32 bytes. A block of size 64 bytes is made |[t0, k, t1, r, i, t2, k, t3]| where |t0, t1, t2, t3| are predefined constant in the spec. Then this block is passed through another function h and the result is XOR'ed with the starting block we just described which gives 64 byte output.


PRG Security Definition
-----------------------

Let |G:K --> {0,1}^n|

Goal: define what it means that |[k <--R-- K, output G(k)]| is indistinguishable from |[r <--R-- {0,1}^n, output r]|

**Statistical tests** can be defined to check whether a given string of bits is random or not. It is basically an algorithm that outputs 0 if not random otherwise 1.

Example - A(x) = 1 iff |len(#0(x) - #1(x)) <= 10 x sqrt(n)|. This checks whether the number of occurences of 0s and 1s are not far apart. There are many more tests like these and they can give a rough idea about whether a string is random or not.

The concept of **Advantage** can be used to check if a statistical test is good or not.

Let |G: K --> {0,1}^n| be a PRG and A a statistical test on |{0,1}^n|, then:

|advantage|

Adv closer to 1 => A can distinguish G from random thus A breaks G which means that generator is no good.

Adv closer to 0 => A cannot distinguish G from random.


We say that |G: K --> {0,1}^n| is a **secure PRG** if for all *efficient* statistical tests, the advantage is negligible. In other words, no efficient algorithm should be able to distinguish a truly random number and psuedorandom number generated by PRG. One thing to keep in mind is that we are only taking into account the "efficient" statistical test.

Are there any provably secure PRGs? No, we cannot. It is unknown whether there are any provably secure PRGs. But we have heuristic candidates.


**A secure PRG is unpredictable**

To prove this, we first prove its contrapositive - PRG predictable |=>| PRG is insecure.

Suppose A is an efficient algorithm which given first i bits can predict i+1 bits such that

|eff_algo|

for non-negligible |e| (e.g. |e| = 1/1000)

If the algorithm is unable to predict the next bit, then the result will be certainly random garbage and so the probability will be 1/2 since there are only two possible value (0 or 1) so it should hit the correct value half number of times. But, if the algorithm is good and able to predict the next bit then the probability will be 1/2 + |e|.

Define statistical test B as:

B(x) = |if A(first i bits of X) = X[i+1] bit then output 1 else output 0|

If A is able to predict the next bit then B outputs 1 else it outputs 0. Now lets try this on on both a truly random number and psuedorandom number.

|when r is a random number: Pr[B(r) = 1] = 1/2|

When r is a truly random number, then algo A would give correct result half of the times. So, the probability that it is correct is also half as shown above.

|when r is a psuedorandom number: Pr[B(G(k)) = 1] > 1/2 + e|

When r is a psuedorandom number, then algo A would be able to identify at least some bits correct so the probability that it is correct greater than 1/2 + |e|.

|Advantage of PRG [B,G] > e|

The advantage of the PRG is greater than |e| that is the difference of the probabilities we calculated above.

So, the algorithm B is able to distinguish the psuedorandom from the random which means that the PRG is insecure. The contrapositive of this is that if the PRG is secure then there are no good statistical tests and so there are no predictors which means the generator is unpredictable.

In fact, the converse is also true. **An unpredictable PRG is secure**. It was proved by Yao in '82.

Let |G: K --> {0,1}^n| be a PRG

Theorem: if |for all i in {0,..,n-1}| PRG G is unpredictable at position i then G is a secure PRG

The idea behind this is that if next-bit predictors cannot distinguish from random then no statistical test can.


**Indistinguishable Distributions**

Let |P1| and |P2| be two distributions over |{0,1}^n|

Def: We say that |P1| and |P2| are computationally indistinguishable in polynomial time (denoted |P1 =p P2|)

if for all efficient statistical tests A

|for x<-P1 Pr[A(x)=1] - for x<-P2 Pr[A(x)=1] < negligible|

Using this notation, we can say that a PRG is secure if |prg_secure_def|


Semantic Security
-----------------

Let's recall Shannon's law for perfect secrecy-

(E, D) has perfect secrecy if |for all m0, m1 in M given len(m1) = len(m2)|

|{E(k,m0)} = {E(k,m1)} where k <-- K|

But the above statement do not hold for all the values of especially when the keys are short. Lets weaken this constraint by saying that rather than requiring both the distributions to be equal, let them be computationally indistinguishable.

|{E(k,m0)} =p {E(k,m1)} where k <-- K|

This definition is still too strong, so lets say that rather than holding for all |m0| and |m1| in message space M, it has to hold for only the |m0|, |m1| pairs that the attacker can exhibit.

**Defining Semantic Security**

For b=0,1 define experiments EXP(0) and EXP(1) as:

Lets say there is a challenger and an adversary. Adversary gives two messages |m0| and |m1| to the challenger. Challenger gives back a cipher text and the adversary has to tell whether the cipher text came from |m0| or |m1|. In EXP(0), challenger gives cipher text of |m0| and in EXP(1), challenger gives cipher text of |m1|.

For b=0,1: |w_b| := [event that EXP(b)=1] (we checking for value 1)

|Advantage (Semantic Security) [A, E] := Pr[W0] - Pr[W1] in [0,1]|

Semantic Security Advantage of Adversary A against scheme E is calculated above. If this advantage is close to 1, it means that the adversary was able to identify the correct messages for both challenger however if the advantage is close to 0, it means adversary wasn't able to distinguish.

Def: E is **semantically secure** if for all efficient adversaries A

|SS Adv[A, E]| is negligible.

In other words, no efficient adversary can distinguish the encryption of |m0| from that of |m1|.

|=>| for all explicit |m0, m1 in M|: |{E(k,m0)} =p {E(k,m1)}|

Example: Suppose that given the CT, efficient adversary A can deduce LSB of PT. Let's prove that the encryption scheme E is not semantically secure.

The adversary gives two messages to challenger, where the LSB of |m0| is 0 and LSB of |m1| is 1. Now, when the challenger gives back a CT, the adversary can look the the CT and deduce LSB. If the LSB is 0, then he can safely say that the it was |m0| or vice-versa. Thus the advantage would be abs(0 - 1) = 1 and adversary is able to clearly distinguish encryption of |m0| from |m1|.

The CT should not reveal any sort information about the PT be it LSB or RSB or i'th bit otherwise the encryption wouldn't be semantically secure.

**OTP is semantically secure**

Adversary gives |m0| and |m1|, challenger gives back CT (xor with the key) of either one. The property of XOR that if a random key k is XOR'ed with either |m0| or |m1|, the distribution is exactly same so the adversary isn't able to identify whether the CT corresponds to |m0| or |m1|. The Semantic Security Advantage in this case would be 0. Therefore, OTP is semantically secure. In fact, it is secure for all adversaries, not just the efficient ones.


Stream Ciphers are Semantically Secure
--------------------------------------

Found this proof a bit confusing and hard to note down. Just watch the last video of section 2.



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
.. |1/256^2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%201/256%5E%7B2%7D
.. |1/256^2 + 1/256^3| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%201/256%5E%7B2%7D%20&plus;%201/256%5E%7B3%7D
.. |{0,1}^s x R --> {0,1}^n| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D%5E%7Bs%7D%20x%20R%20%5Crightarrow%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D%20%5C%20where%5C%20n%20%5Cgg%20s
.. |E(k, m; r) = m xor PRG(k ;r)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20E%28k%2C%20m%20%3B%20r%29%20%3D%20m%20%5Coplus%20PRG%28k%3B%20r%29
.. |{0,1}^(128 or 256) x {0,1}^64 --> {0,1}^n  (max n = 2^73 bits)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D%5E%7B128%5C%20or%5C%20256%7D%20%5C%20x%20%5C%7B0%2C1%5C%7D%5E%7B64%7D%20%5Crightarrow%20%5C%7B0%2C1%5C%7D%5E%7Bn%7D%20%5C%20%5C%20%28max%5C%20n%20%3D%202%5E%7B73%7D%20bits%29
.. |[t0, k, t1, r, i, t2, k, t3]| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Bt_%7B0%7D%2C%20k%2C%20t_%7B1%7D%2C%20r%2C%20i%2C%20t_%7B2%7D%2C%20k%2C%20t_%7B3%7D%5D
.. |t0, t1, t2, t3| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20t_%7B0%7D%2C%20t_%7B1%7D%2C%20t_%7B2%7D%2C%20t_%7B3%7D
.. |G:K --> {0,1}^n| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20G%3AK%20%5Crightarrow%20%5C%7B0%2C1%5C%7D%5En
.. |[k <--R-- K, output G(k)]| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Bk%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K%2C%20output%5C%20G%28k%29%5D
.. |[r <--R-- {0,1}^n, output r]| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Br%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20%5C%7B0%2C1%5C%7D%5En%2C%20output%5C%20r%5D
.. |len(#0(x) - #1(x)) <= 10 x sqrt(n)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%7C%5C%230%28x%29%20-%20%5C%231%28x%29%7C%20%5Cleq%2010%20%5Ccdot%20%5Csqrt%7Bn%7D
.. |{0,1}^n| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5C%7B0%2C1%5C%7D%5En
.. |advantage| image:: http://latex.codecogs.com/png.latex?%5Cdpi%7B150%7D%20%5Cfn_cm%20Adv_%7BPRG%7D%20%5BA%2CG%5D%20%3A%3D%5Cleft%20%7C%20%5CPr%20_%7Bk%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K%7D%20%5BA%28G%28k%29%29%20%3D%201%5D%20-%20%5CPr%20_%7Bk%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20%5C%7B0%2C1%5C%7D%5En%7D%20%5BA%28r%29%20%3D%201%5D%20%5Cright%20%7C%20%5Cin%20%5B0%2C%201%5D
.. |=>| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5CRightarrow
.. |eff_algo| image:: http://latex.codecogs.com/png.latex?%5Cdpi%7B150%7D%20%5Cfn_cm%20%5Csmall%20%5CPr%20_%7Bk%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K%7D%20%5BA%28G%28k%29%7C_%7B1%2C..%2Ci%7D%29%20%3D%20G%28k%29%7C_%7Bi&plus;1%7D%5D%20%3D%20%5Cfrac%7B1%7D%7B2%7D%20&plus;%20%5Cepsilon
.. |if A(first i bits of X) = X[i+1] bit then output 1 else output 0| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20if%5C%20A%28X%7C_%7B1%2C..%2Ci%7D%29%20%3D%20X_%7Bi&plus;1%7D%20%5C%20output%5C%201%5C%20else%5C%20output%5C%200
.. |when r is a random number: Pr[B(r) = 1] = 1/2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20r%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20%5C%7B0%2C1%5C%7D%5En%3A%20Pr%5BB%28r%29%20%3D%201%5D%20%3D%201/2
.. |when r is a psuedorandom number: Pr[B(G(k)) = 1] > 1/2 + e| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20k%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K%3A%20Pr%5BB%28G%28k%29%29%20%3D%201%5D%20%5Cgeq%201/2%20&plus;%20%5Cvarepsilon
.. |Advantage of PRG [B,G] > e| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5CRightarrow%20Adv_%7BPRG%7D%20%5BB%2C%20G%5D%20%3E%20%5Cvarepsilon
.. |for all i in {0,..,n-1}| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20i%20%5Cin%20%5C%7B0%2C...%2Cn-1%5C%7D
.. |P1| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20P_1
.. |P2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20P_2
.. |P1 =p P2| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20P_1%20%5Capprox%20_p%20P_2
.. |for x<-P1 Pr[A(x)=1] - for x<-P2 Pr[A(x)=1] < negligible| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cleft%20%7C%20%5CPr%20_%7Bx%20%5Cleftarrow%20P_1%7D%20%5BA%28x%29%3D1%5D%20-%20%5CPr%20_%7Bx%20%5Cleftarrow%20P_1%7D%20%5BA%28x%29%3D1%5D%20%5Cright%20%7C%20%3C%20negligible
.. |prg_secure_def| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5C%7B%20k%20%5Coverset%7BR%7D%7B%5Cleftarrow%7D%20K%3A%20G%28k%29%20%5C%7D%20%5Capprox%20_p%20uniform%28%5C%7B0%2C1%5C%7D%5En%29
.. |for all m0, m1 in M given len(m1) = len(m2)| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5Cforall%20m_0%2C%20m_1%20%5Cin%20M%5C%20given%5C%20%7Cm1%7C%20%3D%20%7Cm2%7C
.. |{E(k,m0)} = {E(k,m1)} where k <-- K| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5C%7BE%28k%2Cm_0%29%5C%7D%20%3D%20%5C%7BE%28k%2Cm_1%29%5C%7D%20%5C%20where%20%5C%20k%20%5Cleftarrow%20K
.. |{E(k,m0)} =p {E(k,m1)} where k <-- K| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%5C%7BE%28k%2Cm_0%29%5C%7D%20%5Capprox%20_p%20%5C%7BE%28k%2Cm_1%29%5C%7D%20%5C%20where%20%5C%20k%20%5Cleftarrow%20K
.. |w_b| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20W_b
.. |Advantage (Semantic Security) [A, E] := Pr[W0] - Pr[W1] in [0,1]| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20Adv_%7BSS%7D%5BA%2C%20E%5D%20%3A%3D%20%7C%20Pr%5BW_0%5D%20-%20Pr%5BW_1%5D%20%7C%20%5Cin%20%5B0%2C%201%5D
.. |SS Adv[A, E]| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20Adv_%7BSS%7D%5BA%2C%20E%5D
.. |m0, m1 in M| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20m_0%2C%20m_1%20%5Cin%20M
.. |{E(k,m0)} =p {E(k,m1)}| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%20%7BE%28k%2Cm_0%29%7D%20%5Capprox%20_p%20%7BE%28k%2Cm_1%29%7D
.. |2^17| image:: http://latex.codecogs.com/png.latex?%5Cfn_cm%20%5Csmall%202%5E%7B17%7D
