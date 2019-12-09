#ifndef __USR_ENC_H_
#define __USR_ENC_H_

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "mtwister.h"


#define PADDING 0

#define PUBLIC_KEY 1
#define PRIVATE_KEY 0

typedef struct __keypair {
    short type; // Public or Private
    long long int key_part_1;
    long long int key_part_2;
} KeyPair;

char to_lower(char c);
char to_upper(char c);

int mod(int a, int b);
long long int mod_64(long long int a, long long int b);

char *caesar_cipher_encrypt(char *input, int offset);
char *caesar_cipher_decrypt(char *input, int offset);

char *generate_vigenere_key(char *input, int msg_len);
char *vignere_cipher_encrypt(char *input, char *ref);
char *vignere_cipher_decrypt(char *input, char *ref);

int is_square(int x);
char *matrix_cipher_encrypt(char *input, int row, int col);
char *matrix_cipher_decrypt(char *input, int row, int col); // Enter reverse of encrypt as dimensions

int gcd(int a, int b);
int is_prime(long long int n);
long long int generate_prime();
long long int is_coprime(long long int n, long long int m);
long long int generate_coprime(long long int n);
long long int mod_inverse_naive(long long int n, long long int m);
long long int mod_inverse(long long int n, long long int m);
KeyPair *generate_keypairs();
long long int *RSA_encrypt(char *input, KeyPair public);
char *RSA_decrypt(long long int *input, size_t size, KeyPair private);

#endif
