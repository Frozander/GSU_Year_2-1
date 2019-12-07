#include "encryption.h"

char to_lower(char c)
{
    if (isalpha(c))
        c += 'a' - 'A';
    return c;
}

char to_upper(char c)
{
    if (isalpha(c))
        c -= 'a' - 'A';
    return c;
}

// In C % is not a modulo operator but a remainder operator.
// So I had to use a custom mod function
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

// Caesar
char *caesar_cipher_encrypt(char *input, int offset)
{
    char* new_str = strdup(input);
    int str_len = strlen(input);
    
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            if (isupper(new_str[i]))
                new_str[i] = (mod((new_str[i] + offset - 'A'), 26)) + 'A';
            else
                new_str[i] = (mod((new_str[i] + offset - 'a'), 26)) + 'a';
        }
    return new_str;
}

char *caesar_cipher_decrypt(char *input, int offset)
{
    return caesar_cipher_encrypt(input, -offset);
}

// Vigenere

char *generate_vigenere_key(char *input, int msg_len)
{
    char *new_key = malloc(sizeof(char) * msg_len);
    int key_len = strlen(input);
    int j = 0;
    for (size_t i = 0; i < msg_len; ++i, ++j)
    {
        if (j == key_len) j = 0;
        new_key[i] = input[j];
    }
    return new_key;
}

char *vignere_cipher_encrypt(char *input, char *ref)
{
    char *new_str = strdup(input);
    int str_len = strlen(input);

    char *key = generate_vigenere_key(ref, str_len);
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = (input[i] + key[i]);
            if(isupper(new_str[i]))
                new_val = mod(new_val - 'A', 26) + 'A';
            else
                new_val = mod(new_val - 'a', 26) + 'a';
            new_str[i] = new_val;
        }
    free(key);
    return new_str;
}

char *vignere_cipher_decrypt(char *input, char *ref)
{
    char *new_str = strdup(input);
    int str_len = strlen(input);

    char *key = generate_vigenere_key(ref, str_len);
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = (input[i] - key[i]);
            if(isupper(new_str[i]))
                new_val = mod(new_val - 'A', 26) + 'A';
            else
                new_val = mod(new_val - 'a', 26) + 'a';
            new_str[i] = new_val;
        }
    free(key);
    return new_str;
}

char *matrix_cipher_encrypt(char *input, int row, int col)
{
    char *new_str = malloc(strlen(input) * sizeof(char));
    char *matrix = malloc(row * col * sizeof(char));
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
    char *matrix = malloc(row * col * sizeof(char));
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
    uint_fast64_t lower = UINT_FAST64_MAX / 2 + (rand() %  (UINT_FAST64_MAX / 2));
    uint_fast64_t upper = UINT_FAST64_MAX;
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
    return gcd(n, m) == 1;
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

uint_fast64_t mod_inverse_naive(uint_fast64_t n, uint_fast64_t m) 
{ 
    n = n % m;

    for (int d = 1; d < m; ++d) 
        if ((n * d) % m == 1) 
            return d; 
}

uint_fast64_t mod_inverse(uint_fast64_t n, uint_fast64_t m) 
{ 
    uint_fast64_t m1 = m;
    uint_fast64_t y = 0;
    uint_fast64_t x = 1;

    if (m == 1) return 0;

    while(n > 1)
    {
        uint_fast64_t quotient = n / m;

        // Default euclid algorithm for gcd        
        uint_fast64_t t = m;
        m = n % m;
        n = t;

        y = x - quotient * y;
        x = t;
    }

    if (x < 0) x += m1;
    return x;
}

KeyPair *generate_keypairs()
{
    // Public and private keys
    KeyPair *Keys = malloc(sizeof(KeyPair) * 2);

    uint_fast64_t p = generate_prime();
    uint_fast64_t q = generate_prime();

    uint_fast64_t n = p * q;

    uint_fast64_t totient = (p - 1) * (q - 1);
    uint_fast64_t e = generate_coprime(totient);
    uint_fast64_t d = mod_inverse(e, totient);
    
    Keys[0].type = PUBLIC_KEY;
    Keys[0].key_part_1 = e;
    Keys[0].key_part_2 = n;

    Keys[1].type = PRIVATE_KEY;
    Keys[1].key_part_1 = d;
    Keys[1].key_part_2 = n;

    return Keys;
}

char *RSA_encrypt(char *input, KeyPair public);
char *RSA_decrypt(char *input, KeyPair private);