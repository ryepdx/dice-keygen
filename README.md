dice-keygen
===========

A command line app that prompts the user to enter inputs from coin flips, or 4, 8, or 16-sided dice and turns them into a hexadecimal string. Prompted by my own desire to create a cryptographically secure Bitcoin private key offline using dice, and my unhappiness with relying on SHA-256 to produce truly random output, as "dice-wallet" does.

Build instructions:

    gcc -o keygen keygen.c

To go from the hexadecimal private key to a Bitcoin private key and public address with bash (preferably using a Linux live image on an offline, air-gapped computer), use [Lucien Grondilu's bitcoin-bash-tools](https://github.com/grondilu/bitcoin-bash-tools). Assuming you go this route and download `bitcoin.sh` from that project, use it like so:

    source bitcoin.sh
    newBitcoinKey 0x<your hexadecimal key goes here>
