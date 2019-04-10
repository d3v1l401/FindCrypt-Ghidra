# FindCrypt - Ghidra Edition

While for years we used IDA Pro and its incredible plugins developed by its huge community, Ghidra came out recently (at the time of writing) showing a lot of potential and an incredible modular design for customization both in Python or Java.

As most of you know, FindCrypt, a plugin made by nonetheless than Ilfak Guilfanov himself for IDA, is essential for quickly find references to Cryptography functions in the target and extremely useful in the field of Reverse Engineering.

I'm trying to move to Ghidra and the very first thing I noticed is how important is the plugin to me, so I took the responsibility to migrate it, in Java, without sacrificing any signature and try to improve it as well.

![Demo](https://github.com/d3v1l401/FindCrypt-Ghidra/blob/master/Misc/demo.gif)

**This software is being developed and tested, if you encounter any problem please proceed into the Issues section**

## Installation

#### Windows

1. Find your Ghidra installation directory (e.g. "E:\Reversing Softwares\ghidra_9.0")
2. Move "FindCrypt.java" into "Ghidra\Features\BytePatterns\ghidra_scripts"
3. Move "findcrypt_ghidra" (database directory) into "C:\Users\your user\"
4. Be sure Ghidra can access the "findcrypt_ghidra" directory both for reading and writing.

#### Linux

1. Find your Ghidra installation directory (e.g. ~/ghidra)
2. Move "FindCrypt.java" into "~/ghidra/Features/BytePatterns/ghidra_scripts"
3. Move "findcrypt_ghidra" (database directory) into ~/ (or $HOME)
4. Be sure Ghidra can access the "~/findcrypt_ghidra" directory both for reading and writing.

## Usage

Once you started your project and opened the disassembler, use the Script Manager window and search for "FindCrypt.java",
by double clicking or pressing "Run" will execute the script and a result screen is shown if something is found.

![Example result](https://github.com/d3v1l401/FindCrypt-Ghidra/blob/master/Misc/resDemo.png)

### Database

The database is a binary file I serialized myself, it's very easy to understand and very basic but functional for its goal.
The database contains all of the **79** algorithms constants implemented by Ilfak, no sacrifices have been made while migrating them, while also adding more and more by the contributors.

These are the supported algorithms, currently stored in the database being used.

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

#### Database Updating

The script is now using an internal auto update system synchronized with the latest database version in this repository.
The centralized repository synchronization is by default turned on, this is to ensure the user always has the latest version possible
and therefore obtain best results from the script, if you wish to turn it off:

1. Open the "FindCrypt.java" file and find the '__FORCE_NO_DBUPDATE' variable (line 705).
2. Replace "false" with "true".

#### Script Updating

While the database is by design modular and can be updated automatically, the script can not; but the script will check the current version and prompt the user to check this repository latest version for download, with the list of changes from the new version.

The script update message is prompt only once per session.

Proceed to download the latest version of "FindCrypt.java" and replace it in Ghidra's script directory.

Also this feature is turned on by default, if you wish to disable it, follow above mentioned steps on '__FORCE_NO_SCRIPTUPDATE' (line 707).

![Example update](https://github.com/d3v1l401/FindCrypt-Ghidra/blob/master/Misc/updDemo.png)

# Credits
d3vil401 - d3vil401@protonmail.com, d3vil401#7685 (Discord), https://d3vsite.org/

Ilfak Guilfanov - https://twitter.com/ilfak

NSA (Ghidra) - https://ghidra-sre.org/

![Ghidra Logo](https://media.defense.gov/2019/Mar/05/2002096238/400/400/0/190503-D-IM742-3002.PNG)

### License

GNU GPLv3 - Refer to "LICENSE"

Using Crypto++ - Refer to Licenses\Crypto++.txt
