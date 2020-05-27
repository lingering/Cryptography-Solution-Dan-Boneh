# Many time pad
Basiclly the hint shows the fact that when a chatacter xor with space(0x20) it will turn upper to lower or lower to upper(A->a or a->A).A start point to break this kind of stream cipher is based on [frequency of characeters](https://en.wikipedia.org/wiki/Frequency_analysis) appearing in the context of english. Base on that we know the most frequent chars are E T A, and TH ER ON are most common pairs. Observe that a group of  ciphertexts start with "32510b", so "the" is the fair guess combine the facts above(TH is the most common pairand and E is the most frequent letter)
# AES-CBC g++ -maes aes.cpp -o test
Implement AES_CBC MODE in Intel AES-NI library, which is a series customized instruction provied by Intel to accelerate computations of AES. These instructions implement a clear but fine-grained abstruction of AES round/key expansion, so for thoese who dont want to implement AES from scratch is a good solution.

# CBC oracle attack
CBC oracle attack is a classical attack that exploit the different messages return by the oracle server on whether the decrypted text is a valid padding or not.

a trap here is that when try to break the last block the ciphertext, when your guessing bytes is identical to the the origin one the server will return an odd  padding valid message, that will fail the attack fail. So simple way to deal this situtation is to ignore it, and that's the way I use.
