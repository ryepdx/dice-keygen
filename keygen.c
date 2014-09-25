#include <stdio.h>
#include <limits.h>

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)
#define HEXBITS 4

unsigned int get_rng_ceil() {
    unsigned int rng_ceil;

    puts("I assume you are using a Random Number Generator (RNG) that cannot generate zeroes.");
    puts("What is the largest number your RNG can generate?");
    scanf("%d", &rng_ceil);

    return rng_ceil;
}

unsigned int get_rng_input(unsigned int rng_ceil) {
    unsigned int rng_input;

    puts("Enter an input from your RNG: ");
    scanf("%d", &rng_input);

    while (rng_input > rng_ceil) {
        puts("That's higher than your RNG is supposed to be able to generate! Try again: ");
        scanf("%d", &rng_input);
    }

    return rng_input;
}

unsigned int get_key_size() {
    unsigned int key_size;

    puts("How many bits long do you want your key to be?");
    scanf("%d", &key_size);

    return key_size;
}

unsigned int get_bit_length(unsigned int rng_ceil) {
    unsigned int size = 0;

    while (1 << size < rng_ceil) { size++; }

    return size;
}


int is_power_of_two (unsigned int x) {
    if (x < 2) { return 0; }

    while (((x % 2) == 0) && x > 1) {
        x = x >> 1;
    }

    return (x == 1);
}

int main() {
    unsigned int input;
    unsigned int bit_length;
    unsigned int rng_ceil;
    unsigned int key_size;
    unsigned int bits;
    char generate_keys = 'y';

    while(is_power_of_two(rng_ceil = get_rng_ceil()) == 0) {
        puts("Sorry, I can only use powers of 2!");       
    }
    bit_length = get_bit_length(rng_ceil);

    while (generate_keys == 'y' || generate_keys == 'Y') {
        bits = 0;
        key_size = get_key_size();

        char key[BITNSLOTS(key_size)];

        while (bits < key_size) {
            input = (get_rng_input(rng_ceil) - 1);

            for (int i = 0; i < bit_length && bits < key_size; i++) {
                if (input % 2 == 1) {
                    BITSET(key, bits);
                } else {
                    BITCLEAR(key, bits);
                }
                input = input >> 1;
                bits += 1;
            }

            printf("%d of %d bits generated...\n", bits, key_size);
        }

        printf("Your key is:\n0x");
        
        unsigned int chunk = 0;
        for (int i = 0; i < bits; i++) {
            if (BITTEST(key, i)) {
                chunk += 1;
            }

            if (i > 0 && (i+1 % HEXBITS == 0 || i+1 == bits)) {
                printf("%X", chunk);
                chunk = 0;
            } else {
                chunk = chunk << 1;
            }
        }

        puts("\nBe sure to run this through newBitcoinKey in bitcoin.sh first if you are planning on using this to seed a Bitcoin address!");
        puts("Generate another? [y/n]");

        generate_keys = getchar();
        while (generate_keys != 'y' && generate_keys != 'Y' && generate_keys != 'n' && generate_keys != 'N') {
            generate_keys = getchar();
        }
    }
    
    return 0;
}
