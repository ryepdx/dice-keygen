#include <stdio.h>
#include <math.h>
#include <gmp.h>

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
        x /= 2;
    }

    return (x == 1);
}

int main() {
    unsigned int input;
    unsigned int bit_length;
    unsigned int rng_ceil;
    unsigned int key_size;
    mpz_t key;
    unsigned int bits;
    char generate_keys = 'y';

    while(is_power_of_two(rng_ceil = get_rng_ceil()) == 0) {
        puts("Sorry, I can only use powers of 2!");       
    }
    bit_length = get_bit_length(rng_ceil);

    while (generate_keys == 'y' || generate_keys == 'Y') {
        bits = 0;
        mpz_init(key);
        key_size = get_key_size();

        while (bits < key_size) {
            bits += bit_length;

            if (bits > key_size) {
                mpz_mul_ui(key, key, (int) pow(2, key_size % bit_length));
                mpz_add_ui(key, key, ((get_rng_input(rng_ceil)-1) & ((int) pow(2, (key_size % bit_length)+1)-1)));
                bits = key_size;
            } else {
                mpz_mul_ui(key, key, (int) pow(2, bit_length));
                mpz_add_ui(key, key, (get_rng_input(rng_ceil)-1));
            }

            printf("%d of %d bits generated...\n", bits, key_size);
        }

        printf("Your key is:\n 0x");
        mpz_out_str(stdout, 16, key);
        puts("\nGenerate another? [y/n]");

        generate_keys = getchar();
        while (generate_keys != 'y' && generate_keys != 'Y' && generate_keys != 'n' && generate_keys != 'N') {
            generate_keys = getchar();
        }
    }
    
    return 0;
}
