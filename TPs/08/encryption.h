#ifndef __USR_ENC_H_
#define __USR_ENC_H_

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h>

#define PUBLIC_KEY 1
#define PRIVATE_KEY 0

typedef struct __keypair {
    short type; // Public or Private
    uint_fast64_t key_part_1;
    uint_fast64_t key_part_2;
} KeyPair;

char to_lower(char c);
char to_upper(char c);

char *caesar_cipher_encrypt(char *input, int offset);
char *caesar_cipher_decrypt(char *input, int offset);

char *vignere_cipher_encrypt(char *input, char *ref);
char *vignere_cipher_decrypt(char *input, char *ref);

char *matrix_cipher_encrypt(char *input, int row, int col);
char *matrix_cipher_decrypt(char *input, int row, int col); // Enter reverse of encrypt as dimensions

int gcd(int a, int b);
int is_prime(uint_fast64_t n);
KeyPair *generate_keypairs();
char *RSA_encrypt(char *input, KeyPair public);
char *RSA_decrypt(char *input, KeyPair private);

#endif
