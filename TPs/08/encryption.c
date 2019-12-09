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

long long int mod_64(long long int a, long long int b)
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

// Matrix Cipher

int is_square(int x)
{
    int r = sqrt(x);
    if ((r * r) == x) return 1;
}

char *matrix_cipher_encrypt(char *input, int row, int col)
{
    int str_len = strlen(input);
    if(!is_square(str_len)){
        printf("Input is not a square of an integer!\n");
        return input;
    }
    char *new_str = malloc(strlen(input) * sizeof(char));
    char *matrix = malloc(row * col * sizeof(char));
    size_t i, j;
    int cur = 0;

    for (i = 0; i < row; ++i)
        for (j = 0; j < col; ++j)
        {
            if (cur < str_len)
            {
                matrix[j + i * row] = input[cur];
                ++cur;
            }
            else
                matrix[j + i * row] = PADDING;
        }

    cur = 0;

    for (i = 0; i < col; ++i)
        for (j = 0; j < row; ++j)
        {
            if (matrix[i + j * row] == PADDING) continue;
            if (cur < str_len)
            {
                new_str[cur] = matrix[i + j * row];
                ++cur;
            } else break;
        }

    free(matrix);
    return new_str;
}

char *matrix_cipher_decrypt(char *input, int row, int col)
{
    int str_len = strlen(input);
    if(!is_square(str_len)){
        printf("Input is not a square of an integer!\n");
        return input;
    }
    return matrix_cipher_encrypt(input, col, row);
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

int is_prime(long long int n)
{
    long double sqr = sqrtl(n);
    for(int i= 2; i <= sqr; ++i)
        if(n%i==0)
            return 0;
    return 1;
}

long long int generate_prime()
{
    MTRand r = seedRand(time(NULL));
    long long int lower = genRandLong(&r) %  (INT16_MAX/2);
    long long int upper = INT16_MAX;
    int flag;

    printf("Generating Prime... This might take long...\n");
    while (lower < upper)
    {
        if (lower++ % 2 == 0) continue;
        flag = is_prime(lower);
        if (flag == 1) return lower;
        ++lower;
    }
}

long long int is_coprime(long long int n, long long int m)
{
    return gcd(n, m) == 1;
}

long long int generate_coprime(long long int n)
{
    uint64_t coprime;
    MTRand r = seedRand(time(NULL) + __LINE__);
    printf("Generating Coprime... This might take long...\n");
    while (1)
    {
        coprime = (genRandLong(&r) % RAND_MAX - 2) + 2;
        if (is_coprime(coprime, n))
            return coprime;
    }
}

long long int mod_inverse_naive(long long int n, long long int m)
{
    n = n % m;

    for (int d = 1; d < m; ++d)
        if ((n * d) % m == 1)
            return d;
}

long long int mod_inverse(long long int n, long long int m)
{
    long long int m1 = m;
    long long int y = 0;
    long long int x = 1;

    if (m == 1) return 0;

    while(n > 1)
    {
        long long int quotient = n / m;

        // Default euclid algorithm for gcd
        long long int t = m;
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

    long long int p = generate_prime();
    long long int q = generate_prime();
    printf("%lld\n", p);
    printf("%lld\n", q);

    long long int n = p * q;

    long long int totient = (p - 1) * (q - 1);
    long long int e = generate_coprime(totient);
    printf("%lld\n", e);

    long long int d = mod_inverse_naive(e, totient);

    Keys[0].type = PUBLIC_KEY;
    Keys[0].key_part_1 = e;
    Keys[0].key_part_2 = n;

    Keys[1].type = PRIVATE_KEY;
    Keys[1].key_part_1 = d;
    Keys[1].key_part_2 = n;

    return Keys;
}

long long int *RSA_encrypt(char *input, KeyPair public)
{
    size_t str_len = strlen(input);
    long long int *new_str = malloc(sizeof(long long int) * str_len);

    if (public.type == PUBLIC_KEY)
        for (size_t i = 0; i < str_len; ++i)
        {
            new_str[i] = mod_64(input[i] * public.key_part_1, public.key_part_2);
        }
    else
        printf("\nRSA Encryption Error: Not a public key!\n");
    return new_str;
}

char *RSA_decrypt(long long int *input, size_t size, KeyPair private)
{
    char *new_str = malloc(sizeof(char) * size);

    if (private.type == PRIVATE_KEY)
        for (size_t i = 0; i < size; ++i)
        {
            new_str[i] = (char) mod_64(input[i] * private.key_part_1, private.key_part_2);
        }
    else
        printf("\nRSA Decryption Error: Not a public key!\n");
        return new_str;
}
