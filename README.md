# Feistel-cipher-cryptoanalysis.
## kit:
* QT - 5.12.6
* C compiler - MinGw 7.3.0 32-bit for C
* C++ compiler - MinGw 7.3.0 32-bit for C++

This is my student work from cryptography course. This is a QT app with UI, which realises Feistel cypher encryption, and decryption.
This realisation of Feistel cypher handles 64-bit blocks.
Subkeys shcedule is: KS(θ) = (θ<sub>1</sub>,θ<sub>2</sub>,!θ<sub>1</sub>,!θ<sub>2</sub>).
F function is an SP-net with following parametres:
* All S-blocks are equal to (5,8,1,13,10,3,4,2,14,15,12,7,6,0,9,11).
* P block is (11i + 5) mod 16.

Encryptions performs in CBC mode.

The second part of the application is cryptoanalysis. App has functionalities of brute force anf group cryptoanalysis.
