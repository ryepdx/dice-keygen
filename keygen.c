#include <stdio.h>
#include <math.h>

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

    while (pow(2, size) < rng_ceil) { size++; }

    return size;
}


int is_power_of_two (unsigned int x) {
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
    unsigned int key = 0;
    unsigned int bits = 0;

    while(is_power_of_two(rng_ceil = get_rng_ceil()) == 0) {
        puts("Sorry, I can only use powers of 2!");       
    }

    while (is_power_of_two(key_size = get_key_size()) == 0) {
        puts("Sorry, I can only use powers of 2!");
    }

    bit_length = get_bit_length(rng_ceil);

    while (bits < key_size) {
        bits += bit_length;

        if (bits > key_size) {
            key = (key * (int) pow(2, key_size % bit_length)) + ((get_rng_input(rng_ceil)-1) & ((int) pow(2, (key_size % bit_length)+1)-1));
            bits = key_size;
        } else {
            key = (key * (int) pow(2, bit_length)) + (get_rng_input(rng_ceil)-1);
        }

        printf("%d of %d bits generated...\n", bits, key_size);
    }

    printf("Your key is %x\n", key);
    
    return 0;
}
