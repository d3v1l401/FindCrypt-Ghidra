# FindCrypt - Ghidra Edition

While for years we used IDA Pro and its incredible plugins developed by its huge community, Ghidra came out recently (at the time of writing) showing a lot of potential and an incredible modular design for customization both in Python or Java.

As most of you know, FindCrypt, a plugin made by nonetheless than Ilfak himself for IDA, is essential for quickly find references to Cryptography functions in the target and extremely useful in the field of Reverse Engineering.

I'm trying to move to Ghidra and the very first thing I noticed is how important is the plugin to me, so I took the responsibility to migrate it, in Java, without sacrificing any signature.

![Demo](https://puu.sh/D8HVe/f75ea40074.gif)

**This software is being developed and tested, if you encounter any problem please proceed into the Issues section**

## Installation

1. Find your Ghidra installation directory (e.g. "E:\Reversing Softwares\ghidra_9.0")
2. Move "FindCrypt.java" into "Ghidra\Features\BytePatterns\ghidra_scripts"
3. Move "findcrypt_ghidra" (database directory) into "C:\Users\your user\"
4. Be sure "database.d3v" is inside the "findcrypt_ghidra" directory and is accessible by Ghidra (should be by default).

## Usage

Once you started your project and opened the disassembler, use the Script Manager window and search for "FindCrypt.java",
by double clicking or pressing "Run" will execute the script and a result screen is shown if something is found.

![Example result](https://puu.sh/D8HKE/ccd8a3c479.png)

### Database

The database is a binary file I serialized myself, it's very easy to understand and very basic but functional for its goal.
The database contains all of the **79** algorithms constants implemented by Ilfak, no sacrifices have been made while migrating them, while also adding 
more and more by the contributors.

These are the supported algorithms, currently stored in the database being used.

* **Encoders**
	* Base64, Base32
* **Stream ciphers** 
	* Chacha
* **Block ciphers**
    * Blowfish, Camellia, DES, TripleDES, RC2, SHARK, Cast, Square, WAKE, Skipjack 
* **Hash funcions** 
    * Whirlpool, MD2, MD4, MD5, SHA-1, SHA-256, SHA-384, SHA512, Tiger, RIPEMD160, HAVAL, BLAKE2
* **AES Family**
    * AES, RC5/RC6, MARS, Twofish, CAST-256, GOST, SAFER 
* **Compression** 
    * ZLib 

To include more constants of your choice, simply refer to the "FCExporter" project and perhaps also share your new entries :)

# Credits
d3vil401 - d3vil401@protonmail.com / d3vil401@d3vsite.org / https://d3vsite.org/ 

Ilfak Guilfanov - @ilfak

NSA (Ghidra) - https://ghidra-sre.org/


![Ghidra Logo](https://media.defense.gov/2019/Mar/05/2002096238/400/400/0/190503-D-IM742-3002.PNG)

### License

GNU GPLv3
