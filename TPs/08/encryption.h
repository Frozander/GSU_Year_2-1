#ifndef __USR_ENC_H_
#define __USR_ENC_H_

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#define PADDING 36

#define PUBLIC_KEY 1
#define PRIVATE_KEY 0

typedef struct __keypair {
    short type; // Public or Private
    long double key_part_1;
    long double key_part_2;
} KeyPair;

char to_lower(char c);
char to_upper(char c);

int mod(int a, int b);
long double mod_64(long double a, long double b);

char *caesar_cipher_encrypt(char *input, int offset);
char *caesar_cipher_decrypt(char *input, int offset);

char *generate_vigenere_key(char *input, int msg_len);
char *vignere_cipher_encrypt(char *input, char *ref);
char *vignere_cipher_decrypt(char *input, char *ref);

int is_square(int x);
char *matrix_cipher_encrypt(char *input);
char *matrix_cipher_decrypt(char *input); // Enter reverse of encrypt as dimensions

int gcd(int a, int b);
int is_prime(long double n);
long double generate_prime();
long double is_coprime(long double n, long double m);
long double generate_coprime(long double n);
long double mod_inverse_naive(long double n, long double m);
long double mod_inverse(long double n, long double m);
KeyPair *generate_keypairs();
long double *RSA_encrypt(char *input, int p, int q);
char *RSA_decrypt(long double *input, size_t size, int p, int q);
void rsa_print(long double *input, size_t size);

#endif
