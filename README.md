dice-keygen
===========

A command line app that prompts the user to enter inputs from coin flips, or 4, 8, or 16-sided dice and turns them into a hexadecimal string. Prompted by my own desire to create a cryptographically secure Bitcoin private key offline using dice, and my unhappiness with relying on SHA-256 to produce truly random output, as "dice-wallet" does.

Build instructions:

    gcc -o keygen keygen.c -lgmp -lm

Requires [the GNU Multiple Precision Arithmetic Library](https://gmplib.org/).

If you are using this utility to create a Bitcoin private key, specify a bit length of at most 256 when prompted. Also, make sure that the generated hexadecimal string is not larger than `FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141`, which is the maximum value that can be turned into a Bitcoin private key, according to [the wiki](https://en.bitcoin.it/wiki/Private_key#Range_of_valid_private_keys).

To go from the hexadecimal private key to a Bitcoin private key and public address with bash (preferably using a Linux live image on an offline, air-gapped computer), use [Lucien Grondilu's bitcoin-bash-tools](https://github.com/grondilu/bitcoin-bash-tools). Assuming you go this route and download `bitcoin.sh` from that project, use it like so:

    source bitcoin.sh
    newBitcoinKey <your hexadecimal key goes here>

I've also included a copy of Lucien's script in this repository in case the one hosted under his account ever goes offline or is compromised.
