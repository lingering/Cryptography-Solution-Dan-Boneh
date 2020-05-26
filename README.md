# AES-NI_Test g++ -maes
implement AES_CBC MODE in Intel AES-NI library, which is a series customized instruction provied by Intel to accelerate computations of AES. These instructions implement a clear but fine-grained abstruction of AES round/key expansion, so for thoese who dont want to implement AES from scratch is a good solution

# CBC oracle attack
CBC oracle attack is a classical attack that exploit the different messages return by the oracle server on whether the decrypted text is a valid padding or not.

a trap here is that when try to break the last block the ciphertext, when your guessing bytes is identical to the the origin one the server will return an odd  padding valid message, that will fail the attack fail. So simple way to deal this situtation is to ignore it, and that's the way I use.
