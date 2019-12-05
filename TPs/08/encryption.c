#include "encryption.h"

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        c -= 'A' - 'a';
    return c;
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        c += 'A' - 'a';
    return c;
}

// Caesar

char *caesar_cipher_encrypt(char *input, int offset)
{
    offset %= 26;
    char* new_str = strdup(input);
    int str_len = strlen(input);
    // Sanitize
    for (int i = 0; i < str_len; ++i)
        new_str[i] = to_lower(input[i]);
    
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = new_str[i] + offset;
            while (new_val > 'z')
                new_val = (new_val % 'z') + 'a';
            while (new_val < 'a')
                new_val = 'z' - (new_val - 'a');
            new_str[i] = new_val;
        }
    return  new_str;
}

char *caesar_cipher_decrypt(char *input, int offset)
{
    offset %= 26;
    char* new_str = strdup(input);
    int str_len = strlen(input);
    // Sanitize
    for (int i = 0; i < str_len; ++i)
        new_str[i] = to_lower(input[i]);
    
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = new_str[i] - offset;
            while (new_val > 'z')
                new_val = (new_val % 'z') + 'a';
            while (new_val < 'a')
                new_val = 'z' - (new_val - 'a');
            new_str[i] = new_val;
        }
    return  new_str;
}

// Vigenere

char *vignere_cipher_encrypt(char *input, char *ref)
{
    char *new_str = strdup(input);
    int str_len = strlen(input);

    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = (input[i] + ref[i]) % 26;

            new_val += 'A';
            new_str[i] = new_val;
        }
    return new_str;
}

char *vignere_cipher_decrypt(char *input, char *ref)
{
    char *new_str = strdup(input);
    int str_len = strlen(input);

    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = (input[i] - ref[i]) % 26;

            new_val += 'A';
            new_str[i] = new_val;
        }
    return new_str;
}

char *matrix_cipher_encrypt(char *input, int row, int col)
{
    char *new_str = malloc(strlen(input) * sizeof(char));
    char *matrix = malloc(n * m * sizeof(char));
    int str_len = strlen(input);
    size_t i, j;
    int cur = 0;

    for (i = 0; i < row; ++i)
        for (j = 0; j < col; ++j)
            while (cur < str_len)
            {
                matrix[j + i * row] = input[cur++];
            }

    cur = 0;
    
    for (i = 0; i < col; ++i)
        for (j = 0; j < row; ++j)
            while (cur < str_len)
            {
                new_str[cur++] = matrix[i + j * row];
            }

    return new_str;    
}

char *matrix_cipher_decrypt(char *input, int row, int col)
{
    char *new_str = malloc(strlen(input) * sizeof(char));
    char *matrix = malloc(n * m * sizeof(char));
    int str_len = strlen(input);
    size_t i, j;
    int cur = 0;

    
    for (i = 0; i < col; ++i)
        for (j = 0; j < row; ++j)
            if (!(cur < str_len)) break;
            matrix[j + i * row] = input[cur++];

    cur = 0;
    
    for (i = 0; i < row; ++i)
        for (j = 0; j < col; ++j)
            if (!(cur < str_len)) break;
            new_str[cur++] = matrix[i + j * row];

    return new_str;    
}

int gcd(int a, int b)
{
    int tmp;
    while(1)
    {
        tmp = a % b;
        if (tmp == 0)
            return b;
        a = b;
        b = tmp;
    }
}

int is_prime(uint_fast64_t n)
{
    long double sqr = sqrtl(n);
    for(int i= 2; i <= sqr; ++i)
        if(n%i==0)
            return 0;
    return 1;
}

uint_fast64_t generate_prime()
{
    uint_fast64_t lower = INT64_MAX / 2 + (rand() %  (INT64_MAX / 2));
    uint_fast64_t upper = INT64_MAX;
    int flag;

    while (lower < upper)
    {
        flag = is_prime(lower);
        if (flag == 1) return lower;
        ++lower;
    }
}

uint_fast64_t is_coprime(uint_fast64_t n, uint_fast64_t m)
{
    if (gcd(n, m) == 1) return 1;
    return 0;
}

uint_fast64_t generate_coprime(uint_fast64_t n) { 
    uint64_t coprime;
    while (1)
    {
        coprime = (rand() % RAND_MAX - 2) + 2;
        if (is_coprime(coprime, n))
            return coprime;
    }
}

KeyPair *generate_keypairs()
{
    uint_fast64_t p = generate_prime();
    uint_fast64_t q = generate_prime();

    uint_fast64_t n = p * q;

    uint_fast64_t totient = (p - 1) * (q - 1);
    uint_fast64_t e = generate_coprime(totient);
    

}

char *RSA_encrypt(char *input, KeyPair public);
char *RSA_decrypt(char *input, KeyPair private);